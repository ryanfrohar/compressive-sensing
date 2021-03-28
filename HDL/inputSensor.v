`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/22/2021 02:01:10 PM
// Design Name: 
// Module Name: inputSensor
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


module inputSensor(clk, reset, ja0, out);
    input clk, reset;
    input [7:0] ja0;
    output reg [7:0] out; 
        
    always@(posedge clk)
        if(reset)
            begin
                out <= 8'b0;
            end
        else
            begin
                out <= ja0;
            end     
    
endmodule
