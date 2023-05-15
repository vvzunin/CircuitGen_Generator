//f0 = 1'b1
//f1 = (not x0 and not x1 and x2) or (x0 and x1 and not x2) or (x0 and x1 and x2)
//f2 = (not x0 and not x1 and not x2) or (not x0 and x1 and not x2) or (not x0 and x1 and x2) or (x0 and not x1 and x2)
//f3 = (not x0 and not x1 and not x2) or (not x0 and not x1 and x2) or (x0 and not x1 and not x2)
//f4 = (not x0 and not x1 and x2) or (not x0 and x1 and x2) or (x0 and not x1 and not x2) or (x0 and x1 and not x2) or (x0 and x1 and x2)
//f5 = (not x0 and x1 and x2) or (x0 and x1 and x2)
module CCGRTT1196_CNFT(
	input x0, x1, x2,
	output f0, f1, f2, f3, f4, f5
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26;

	assign f0 = 1'b1;
	assign f1 = d1;
	or (d1, d2, d6);
	and (d2, d3, d4);
	not (d3, x0);
	and (d4, d5, x2);
	not (d5, x1);
	or (d6, d7, d10);
	and (d7, x0, d8);
	and (d8, x1, d9);
	not (d9, x2);
	and (d10, x0, d11);
	and (d11, x1, x2);
	assign f2 = d12;
	or (d12, d13, d15);
	and (d13, d3, d14);
	and (d14, d5, d9);
	or (d15, d16, d17);
	and (d16, d3, d8);
	or (d17, d18, d19);
	and (d18, d3, d11);
	and (d19, x0, d4);
	assign f3 = d20;
	or (d20, d13, d21);
	or (d21, d2, d22);
	and (d22, x0, d14);
	assign f4 = d23;
	or (d23, d2, d24);
	or (d24, d18, d25);
	or (d25, d6, d22);
	assign f5 = d26;
	or (d26, d10, d18);
endmodule
