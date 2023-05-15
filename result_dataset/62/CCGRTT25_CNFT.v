//f0 = (x0 and x1)
//f1 = 1'b1
module CCGRTT25_CNFT(
	input x0, x1,
	output f0, f1
);

	wire d1;

	assign f0 = d1;
	and (d1, x0, x1);
	assign f1 = 1'b1;
endmodule
