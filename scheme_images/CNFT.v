//f0 = 1'b0
//f1 = (not x0 and x1)
module CNFT(
	input x0, x1,
	output f0, f1
);

	wire wr0, wr1;

	assign f0 = 1'b0;
	assign f1 = wr0;
	and (wr0, wr1, x1);
	not (wr1, x0);
endmodule
