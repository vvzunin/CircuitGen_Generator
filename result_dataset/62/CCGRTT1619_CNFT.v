//f0 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and x2 and not x3)
//f1 = (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3)
//f2 = (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3)
//f3 = (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and x3)
module CCGRTT1619_CNFT(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58;

	assign f0 = d1;
	or (d1, d2, d9);
	and (d2, d3, d4);
	not (d3, x0);
	and (d4, d5, d6);
	not (d5, x1);
	and (d6, d7, d8);
	not (d7, x2);
	not (d8, x3);
	or (d9, d10, d13);
	and (d10, d3, d11);
	and (d11, d5, d12);
	and (d12, x2, x3);
	or (d13, d14, d17);
	and (d14, d3, d15);
	and (d15, x1, d16);
	and (d16, d7, x3);
	or (d17, d18, d21);
	and (d18, d3, d19);
	and (d19, x1, d20);
	and (d20, x2, d8);
	or (d21, d22, d23);
	and (d22, x0, d4);
	or (d23, d24, d25);
	and (d24, x0, d11);
	or (d25, d26, d28);
	and (d26, x0, d27);
	and (d27, x1, d6);
	and (d28, x0, d19);
	assign f1 = d29;
	or (d29, d10, d30);
	or (d30, d31, d32);
	and (d31, d3, d27);
	or (d32, d14, d33);
	or (d33, d18, d34);
	or (d34, d22, d35);
	or (d35, d36, d38);
	and (d36, x0, d37);
	and (d37, d5, d16);
	or (d38, d24, d39);
	or (d39, d28, d40);
	and (d40, x0, d15);
	assign f2 = d41;
	or (d41, d31, d42);
	or (d42, d14, d43);
	or (d43, d18, d44);
	or (d44, d45, d47);
	and (d45, x0, d46);
	and (d46, d5, d20);
	or (d47, d26, d40);
	assign f3 = d48;
	or (d48, d49, d50);
	and (d49, d3, d46);
	or (d50, d51, d53);
	and (d51, d3, d52);
	and (d52, x1, d12);
	or (d53, d36, d54);
	or (d54, d45, d55);
	or (d55, d24, d56);
	or (d56, d26, d57);
	or (d57, d40, d58);
	and (d58, x0, d52);
endmodule
