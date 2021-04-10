module sending(clk, SCK, MISO, SSEL, data, signalReceived, byteSent);

input clk;
input SCK;
output MISO;
input SSEL;
input [7:0] data;
input signalReceived;
output byteSent;

reg byte_sent;
assign byteSent = byte_sent;

//reg firstTime = 1'b1;

reg [7:0] byte_data_sent;
reg byte_sent_2clk = 1'b0;

reg [2:0] cnt;

// sync SCK to the FPGA clock using a 3-bits shift register
reg [2:0] SCKr;  

always @(posedge clk) 
begin
 SCKr <= {SCKr[1:0], SCK};
end

wire SCK_risingedge = (SCKr[2:1]==2'b01);  // now we can detect SCK rising edges
wire SCK_fallingedge = (SCKr[2:1]==2'b10);  // and falling edges

// same thing for SSEL
reg [2:0] SSELr;  

always @(posedge clk) 
begin
  SSELr <= {SSELr[1:0], SSEL};
end

wire SSEL_active = ~SSELr[1];  // SSEL is active low
wire SSEL_startmessage = (SSELr[2:1]==2'b10);  // message starts at falling edge
wire SSEL_endmessage = (SSELr[2:1]==2'b01);  // message stops at rising edge


always @(posedge clk) 
begin
  if(signalReceived)
  begin
    if(~SSEL_active) 
    begin
      cnt<=3'b000;  // count the messages
    end
    else
    begin
      if(byte_sent_2clk)
      begin
        byte_data_sent <= data;
      end
      if(SCK_risingedge)
      begin
        cnt <= cnt + 3'b001;
        byte_data_sent <= {byte_data_sent[6:0], 1'b0};
      end
    end
  end
end

always @(posedge clk)
begin
  if(signalReceived)
  begin
    if (byte_sent_2clk)
    begin
      byte_sent_2clk <= 1'b0;
    end
    if (byte_sent)
    begin
      byte_sent_2clk <= 1'b1;
      byte_sent <= SSEL_active && SCK_risingedge && (cnt==3'b111);
    end
    else
    begin
      byte_sent <= SSEL_active && SCK_risingedge && (cnt==3'b111);
    end
  end
end

assign MISO = byte_data_sent[7];  // send MSB first
// we assume that there is only one slave on the SPI bus
// so we don't bother with a tri-state buffer for MISO
// otherwise we would need to tri-state MISO when SSEL is inactive

endmodule