`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/22/2021 02:52:04 PM
// Design Name: 
// Module Name: inputSensorTest
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


module inputSensorTest;
    
    reg [7:0] in;
    reg [7:0] out;
    reg reset;
    reg clk;
    reg [7:0] data[255:0];
    integer file, i;

    inputSensor dut(.clk(clk), .reset(reset), .ja0(in), .out(out));
    
    always #1000 clk = ~clk;
    
    initial begin
        file = $fopen("output.txt", "w");
            
        #1000000;
            
        for (i=0; i<256; i=i+1)
        begin
            $fwrite(file, "%b\n", data[i]);
        end
            
        $fclose(file);
        
    end
    
    initial 
        begin
            clk = 1'b0;
            for (i=0; i<256; i=i+1)
                @(posedge clk)
                    data[i] <= out;
        end
        
endmodule
