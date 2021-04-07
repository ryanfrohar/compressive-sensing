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


wire [7:0] dataByte;
wire [7:0] sendByte;

reg [7:0] compressedX [63:0];
reg [6:0] inputCounter = 7'b0000000;

reg byte_receieved;
reg signalReceived;

//RAND MAT STUFF
reg randReceived;
reg [7:0] phiSignal [16383:0];
reg [14:0] randCounter = 15'b000000000000000;

wire byteSent;

integer i=0;
integer j=-1;
integer k=0;

reg [7:0] reconstructed_Signal [255:0];
assign sendByte = reconstructed_Signal[j];

signalReceive srA(.clk(clk), .SCK(SCK), .MOSI(MOSI), .byteReceived(byte_received), .dataByte(dataByte), .SSEL(SSEL));

always @(posedge clk)
begin 
  if(~signalReceived)
  begin
    if(byte_received)
    begin
      compressedX[i] <= dataByte;
      i=i+1;
      inputCounter <= inputCounter + 7'b0000001; 
    end
  end
end

always @(posedge clk)
begin
 if(signalReceived && ~randReceived)
  begin
    if(byte_received)
    begin
      phiSignal[k] <= dataByte;
      k=k+1;
      randCounter <= randCounter + 15'b000000000000001; 
    end
  end
end

always @(posedge clk)
begin
  signalReceived <= (inputCounter == 7'b1000000);
  randReceived <= (randCounter == 15'b100000000000000);
end


/**
OMP STUFF
**/

integer m=0;

/**
initial begin
    for(m=0;m<16383;m=m+1)begin
        phiSignal[m]= 32'b0;
    end
end
**/

wire ap_rst;
assign ap_rst =1'b0;
wire ap_start;
assign ap_start = randReceived;
wire ap_done;
wire ap_idle;
wire ap_ready;
wire [13:0] randy_address0;
wire randy_ce0;
reg [31:0] randy_q0;
wire [5:0] xsig_address0;
wire xsig_ce0;
reg [31:0] xsig_q0;
wire [7:0] reconstructedX_address0;
wire reconstructedX_ce0;
wire reconstructedX_we0;
wire [31:0] reconstructedX_d0;
wire [31:0] ap_return;

OMP_0 omp_inst(.ap_clk(clk),
             .ap_rst(ap_rst),
             .ap_start(ap_start),
             .ap_done(ap_done),
             .ap_idle(ap_idle),
             .ap_ready(ap_ready),
             .randy_address0(randy_address0),
             .randy_ce0(randy_ce0),
             .randy_q0(randy_q0),
             .xsig_address0(xsig_address0),
             .xsig_ce0(xsig_ce0),
             .xsig_q0(xsig_q0),
             .reconstructedX_address0(reconstructedX_address0),
             .reconstructedX_ce0(reconstructedX_ce0),
             .reconstructedX_we0(reconstructedX_we0),
             .reconstructedX_d0(reconstructedX_d0),
             .ap_return(ap_return));

always @(posedge clk)
begin
    if (reconstructedX_ce0) begin
        if (reconstructedX_we0) 
            reconstructed_Signal[reconstructedX_address0] <= reconstructedX_d0[7:0]; 
    end
end

always @(posedge clk)
begin
    if (randy_ce0) begin
        randy_q0 <= {24'b0, phiSignal[randy_address0]};
    end
end

always @(posedge clk)
begin
    if (xsig_ce0) begin
        xsig_q0 <= {24'b0, compressedX[xsig_address0]};
    end
end


sending sB(.clk(clk), .SCK(SCK), .MISO(MISO), .SSEL(SSEL), .done(ap_done), .data(sendByte), .signalReceived(randReceived), .byteSent(byteSent));

always @(posedge clk)
begin
  if(randReceived && ap_done)
  begin
    if(byteSent)
    begin
      j=j+1;
    end 
  end
end



endmodule