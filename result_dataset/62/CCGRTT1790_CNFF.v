//f0 = (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3)
//f1 = (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f2 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f3 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or not x2 or x3)
//f4 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3)
module CCGRTT1790_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66;

	assign f0 = d1;
	and (d1, d2, d7);
	or (d2, x0, d3);
	or (d3, d4, d5);
	not (d4, x1);
	or (d5, x2, d6);
	not (d6, x3);
	and (d7, d8, d12);
	or (d8, x0, d9);
	or (d9, d4, d10);
	or (d10, x3, d11);
	not (d11, x2);
	and (d12, d13, d16);
	or (d13, x0, d14);
	or (d14, d4, d15);
	or (d15, d6, d11);
	and (d16, d17, d21);
	or (d17, d18, d19);
	not (d18, x0);
	or (d19, x1, d20);
	or (d20, x2, x3);
	or (d21, d18, d22);
	or (d22, x1, d5);
	assign f1 = d23;
	and (d23, d24, d26);
	or (d24, x0, d25);
	or (d25, x1, d10);
	and (d26, d27, d29);
	or (d27, x0, d28);
	or (d28, x1, d15);
	and (d29, d30, d32);
	or (d30, x0, d31);
	or (d31, d4, d20);
	and (d32, d33, d34);
	or (d33, d18, d25);
	and (d34, d35, d36);
	or (d35, d18, d31);
	and (d36, d37, d38);
	or (d37, d9, d18);
	or (d38, d14, d18);
	assign f2 = d39;
	and (d39, d40, d41);
	or (d40, x0, d19);
	and (d41, d42, d43);
	or (d42, x0, d22);
	and (d43, d24, d44);
	and (d44, d2, d45);
	and (d45, d21, d46);
	and (d46, d33, d47);
	and (d47, d48, d49);
	or (d48, d18, d28);
	and (d49, d38, d50);
	or (d50, d3, d18);
	assign f3 = d51;
	and (d51, d42, d52);
	and (d52, d27, d53);
	and (d53, d2, d54);
	and (d54, d8, d55);
	and (d55, d13, d56);
	and (d56, d21, d57);
	and (d57, d33, d58);
	and (d58, d37, d48);
	assign f4 = d59;
	and (d59, d42, d60);
	and (d60, d27, d61);
	and (d61, d30, d62);
	and (d62, d8, d63);
	and (d63, d13, d64);
	and (d64, d21, d65);
	and (d65, d33, d66);
	and (d66, d35, d48);
endmodule
