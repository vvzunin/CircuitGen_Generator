//f0 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and x2 and x3)
//f1 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and not x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and not x2 and not x3)
//f2 = (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and x1 and x2 and not x3)
//f3 = (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and x3)
//f4 = (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and x2 and x3)
module CCGRTT1779_CNFT(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63;

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
	and (d12, x2, d8);
	or (d13, d14, d17);
	and (d14, d3, d15);
	and (d15, x1, d16);
	and (d16, d7, x3);
	or (d17, d18, d21);
	and (d18, d3, d19);
	and (d19, x1, d20);
	and (d20, x2, x3);
	and (d21, x0, d22);
	and (d22, d5, d20);
	assign f1 = d23;
	or (d23, d2, d24);
	or (d24, d25, d27);
	and (d25, d3, d26);
	and (d26, d5, d16);
	or (d27, d10, d28);
	or (d28, d14, d29);
	or (d29, d30, d31);
	and (d30, x0, d4);
	or (d31, d32, d33);
	and (d32, x0, d11);
	and (d33, x0, d34);
	and (d34, x1, d6);
	assign f2 = d35;
	or (d35, d25, d36);
	or (d36, d10, d37);
	or (d37, d38, d39);
	and (d38, d3, d22);
	or (d39, d14, d40);
	or (d40, d41, d43);
	and (d41, d3, d42);
	and (d42, x1, d12);
	or (d43, d30, d44);
	or (d44, d45, d46);
	and (d45, x0, d26);
	and (d46, x0, d42);
	assign f3 = d47;
	or (d47, d25, d48);
	or (d48, d10, d49);
	or (d49, d38, d50);
	or (d50, d51, d52);
	and (d51, d3, d34);
	or (d52, d45, d53);
	or (d53, d32, d54);
	or (d54, d55, d56);
	and (d55, x0, d15);
	and (d56, x0, d19);
	assign f4 = d57;
	or (d57, d10, d58);
	or (d58, d14, d59);
	or (d59, d18, d60);
	or (d60, d30, d61);
	or (d61, d45, d62);
	or (d62, d32, d63);
	or (d63, d21, d56);
endmodule
