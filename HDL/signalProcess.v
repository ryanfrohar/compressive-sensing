`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/31/2021 10:48:55 AM
// Design Name: 
// Module Name: signalProcess
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


module signalProcess(clk, SCK, MOSI, MISO, SSEL);
input clk;

input SCK, SSEL, MOSI;

output MISO;

reg [7:0] dataByte;

reg [7:0] compressedX [63:0];
reg [5:0] inputCounter = 6'b000000;

reg byte_receieved;
reg signalReceived;

integer i=0;

signalReceive srA(.clk(clk), .SCK(SCK), .MOSI(MOSI), .byteReceived(byte_received), .dataByte(dataByte), .SSEL(SSEL));

always @(posedge clk)
begin 
  if(byte_received)
  begin
    compressedX[i] <= dataByte;
    i=i+1;
    inputCounter <= inputCounter + 6'b000001;  
    if(signalReceived)
    begin
      i=0;
    end
  end
end

always@(posedge clk)
begin
  signalReceived <= (inputCounter == 6'b111111);
end



endmodule
