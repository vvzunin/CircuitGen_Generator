//f0 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3)
//f1 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or x3)
//f2 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3)
//f3 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f4 = (x0 or x1 or x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f5 = (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or not x1 or not x2 or x3)
module CCGRTT1815_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68, d69, d70, d71;

	assign f0 = d1;
	and (d1, d2, d5);
	or (d2, x0, d3);
	or (d3, x1, d4);
	or (d4, x2, x3);
	and (d5, d6, d10);
	or (d6, x0, d7);
	or (d7, x1, d8);
	or (d8, x3, d9);
	not (d9, x2);
	and (d10, d11, d16);
	or (d11, x0, d12);
	or (d12, d13, d14);
	not (d13, x1);
	or (d14, d9, d15);
	not (d15, x3);
	and (d16, d17, d19);
	or (d17, d3, d18);
	not (d18, x0);
	and (d19, d20, d21);
	or (d20, d7, d18);
	or (d21, d18, d22);
	or (d22, x1, d14);
	assign f1 = d23;
	and (d23, d24, d27);
	or (d24, x0, d25);
	or (d25, x1, d26);
	or (d26, x2, d15);
	and (d27, d6, d28);
	and (d28, d29, d31);
	or (d29, x0, d30);
	or (d30, d13, d26);
	and (d31, d11, d32);
	and (d32, d33, d35);
	or (d33, d18, d34);
	or (d34, d4, d13);
	or (d35, d18, d36);
	or (d36, d8, d13);
	assign f2 = d37;
	and (d37, d2, d38);
	and (d38, d39, d40);
	or (d39, x0, d22);
	and (d40, d41, d42);
	or (d41, x0, d36);
	and (d42, d11, d43);
	and (d43, d20, d44);
	and (d44, d35, d45);
	or (d45, d18, d30);
	assign f3 = d46;
	and (d46, d24, d47);
	and (d47, d6, d48);
	and (d48, d49, d50);
	or (d49, x0, d34);
	and (d50, d41, d51);
	and (d51, d11, d52);
	and (d52, d17, d53);
	and (d53, d54, d55);
	or (d54, d18, d25);
	and (d55, d21, d56);
	or (d56, d12, d18);
	assign f4 = d57;
	and (d57, d2, d58);
	and (d58, d39, d59);
	and (d59, d49, d60);
	and (d60, d29, d61);
	and (d61, d17, d62);
	and (d62, d54, d63);
	and (d63, d20, d64);
	and (d64, d33, d65);
	and (d65, d45, d56);
	assign f5 = d66;
	and (d66, d6, d67);
	and (d67, d39, d68);
	and (d68, d49, d69);
	and (d69, d29, d70);
	and (d70, d41, d71);
	and (d71, d17, d35);
endmodule
