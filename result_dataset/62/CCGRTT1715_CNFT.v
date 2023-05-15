//f0 = (not x0 and not x1 and not x2 and x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3)
//f1 = (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and x2 and x3)
//f2 = (not x0 and not x1 and not x2 and not x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and x3)
//f3 = (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (x0 and not x1 and not x2 and x3)
//f4 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and x3) or (x0 and x1 and not x2 and not x3)
module CCGRTT1715_CNFT(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59;

	assign f0 = d1;
	or (d1, d2, d8);
	and (d2, d3, d4);
	not (d3, x0);
	and (d4, d5, d6);
	not (d5, x1);
	and (d6, d7, x3);
	not (d7, x2);
	or (d8, d9, d11);
	and (d9, d3, d10);
	and (d10, x1, d6);
	or (d11, d12, d16);
	and (d12, d3, d13);
	and (d13, x1, d14);
	and (d14, x2, d15);
	not (d15, x3);
	or (d16, d17, d20);
	and (d17, x0, d18);
	and (d18, d5, d19);
	and (d19, d7, d15);
	or (d20, d21, d23);
	and (d21, x0, d22);
	and (d22, d5, d14);
	or (d23, d24, d27);
	and (d24, x0, d25);
	and (d25, d5, d26);
	and (d26, x2, x3);
	or (d27, d28, d29);
	and (d28, x0, d10);
	and (d29, x0, d13);
	assign f1 = d30;
	or (d30, d31, d32);
	and (d31, d3, d22);
	or (d32, d33, d34);
	and (d33, d3, d25);
	or (d34, d9, d35);
	or (d35, d24, d36);
	or (d36, d37, d39);
	and (d37, x0, d38);
	and (d38, x1, d19);
	and (d39, x0, d40);
	and (d40, x1, d26);
	assign f2 = d41;
	or (d41, d42, d43);
	and (d42, d3, d18);
	or (d43, d44, d45);
	and (d44, d3, d38);
	or (d45, d12, d46);
	or (d46, d47, d48);
	and (d47, d3, d40);
	or (d48, d17, d24);
	assign f3 = d49;
	or (d49, d2, d50);
	or (d50, d31, d51);
	and (d51, x0, d4);
	assign f4 = d52;
	or (d52, d42, d53);
	or (d53, d2, d54);
	or (d54, d33, d55);
	or (d55, d44, d56);
	or (d56, d9, d57);
	or (d57, d12, d58);
	or (d58, d47, d59);
	or (d59, d37, d51);
endmodule
