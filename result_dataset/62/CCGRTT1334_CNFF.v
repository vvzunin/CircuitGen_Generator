//f0 = (x0 or x1 or x2) and (x0 or not x1 or not x2) and (not x0 or x1 or x2) and (not x0 or x1 or not x2) and (not x0 or not x1 or x2) and (not x0 or not x1 or not x2)
//f1 = (x0 or x1 or x2) and (x0 or not x1 or x2) and (x0 or not x1 or not x2) and (not x0 or not x1 or x2)
//f2 = (x0 or x1 or x2) and (x0 or x1 or not x2) and (x0 or not x1 or x2) and (not x0 or x1 or x2) and (not x0 or x1 or not x2) and (not x0 or not x1 or not x2)
//f3 = (x0 or not x1 or x2) and (not x0 or x1 or x2) and (not x0 or not x1 or not x2)
//f4 = (x0 or x1 or x2) and (x0 or not x1 or not x2) and (not x0 or x1 or x2) and (not x0 or not x1 or x2) and (not x0 or not x1 or not x2)
//f5 = (x0 or x1 or not x2) and (not x0 or x1 or x2) and (not x0 or not x1 or x2)
//f6 = (x0 or not x1 or x2) and (not x0 or x1 or x2) and (not x0 or not x1 or not x2)
//f7 = (x0 or not x1 or not x2) and (not x0 or x1 or x2) and (not x0 or x1 or not x2) and (not x0 or not x1 or x2)
module CCGRTT1334_CNFF(
	input x0, x1, x2,
	output f0, f1, f2, f3, f4, f5, f6, f7
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38;

	assign f0 = d1;
	and (d1, d2, d4);
	or (d2, x0, d3);
	or (d3, x1, x2);
	and (d4, d5, d9);
	or (d5, x0, d6);
	or (d6, d7, d8);
	not (d7, x1);
	not (d8, x2);
	and (d9, d10, d12);
	or (d10, d3, d11);
	not (d11, x0);
	and (d12, d13, d15);
	or (d13, d11, d14);
	or (d14, x1, d8);
	and (d15, d16, d18);
	or (d16, d11, d17);
	or (d17, x2, d7);
	or (d18, d6, d11);
	assign f1 = d19;
	and (d19, d2, d20);
	and (d20, d21, d22);
	or (d21, x0, d17);
	and (d22, d5, d16);
	assign f2 = d23;
	and (d23, d2, d24);
	and (d24, d25, d26);
	or (d25, x0, d14);
	and (d26, d21, d27);
	and (d27, d10, d28);
	and (d28, d13, d18);
	assign f3 = d29;
	and (d29, d21, d30);
	and (d30, d10, d18);
	assign f4 = d31;
	and (d31, d2, d32);
	and (d32, d5, d33);
	and (d33, d10, d15);
	assign f5 = d34;
	and (d34, d25, d35);
	and (d35, d10, d16);
	assign f6 = d29;
	assign f7 = d36;
	and (d36, d5, d37);
	and (d37, d10, d38);
	and (d38, d13, d16);
endmodule
