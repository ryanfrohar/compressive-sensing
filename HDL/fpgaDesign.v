`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/30/2021 05:28:35 PM
// Design Name: 
// Module Name: omp
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module signalReceive(clk, SCK, MOSI, byteReceived, dataByte, SSEL);
input clk;

input SCK, SSEL, MOSI;

output byteReceived;
output [7:0] dataByte;


// we handle SPI in 8-bits format, so we need a 3 bits counter to count the bits as they come in
reg [2:0] bitcnt;
reg byte_received=1'b0;  // high when a byte has been received
reg [7:0] byte_data_received;

assign byteReceived = byte_received;

assign dataByte = byte_data_received;

// sync SCK to the FPGA clock using a 3-bits shift register
reg [2:0] SCKr;  
// same thing for SSEL
reg [2:0] SSELr;  
// and for MOSI
reg [1:0] MOSIr; 

always @(posedge clk) 
begin
  SCKr <= {SCKr[1:0], SCK};
end

wire SCK_risingedge = (SCKr[2:1]==2'b01);  // now we can detect SCK rising edges
wire SCK_fallingedge = (SCKr[2:1]==2'b10);  // and falling edges

always @(posedge clk) 
begin
  SSELr <= {SSELr[1:0], SSEL};
end

wire SSEL_active = ~SSELr[1];  // SSEL is active low
wire SSEL_startmessage = (SSELr[2:1]==2'b10);  // message starts at falling edge
wire SSEL_endmessage = (SSELr[2:1]==2'b01);  // message stops at rising edge

 
always @(posedge clk) 
begin
  MOSIr <= {MOSIr[0], MOSI};
end

wire MOSI_data = MOSIr[1];

always @(posedge clk)
begin
  if(~SSEL_active)
  begin
    bitcnt <= 3'b000;
  end
  else
  begin
    if(SCK_risingedge)
    begin
      bitcnt <= bitcnt + 3'b001;
      // implement a shift-left register (since we receive the data MSB first)
      byte_data_received <= {byte_data_received[6:0], MOSI_data};
    end
  end
end

always @(posedge clk)
begin    
    byte_received <= SSEL_active && SCK_risingedge && (bitcnt==3'b111);
end 

endmodule
