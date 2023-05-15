//f0 = (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f1 = (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f2 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3)
//f3 = (x0 or x1 or x2 or x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f4 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
module CCGRTT1797_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68;

	assign f0 = d1;
	and (d1, d2, d6);
	or (d2, x0, d3);
	or (d3, x1, d4);
	or (d4, d5, x3);
	not (d5, x2);
	and (d6, d7, d11);
	or (d7, x0, d8);
	or (d8, x1, d9);
	or (d9, d5, d10);
	not (d10, x3);
	and (d11, d12, d16);
	or (d12, x0, d13);
	or (d13, d14, d15);
	not (d14, x1);
	or (d15, x2, x3);
	and (d16, d17, d19);
	or (d17, x0, d18);
	or (d18, d4, d14);
	and (d19, d20, d22);
	or (d20, d8, d21);
	not (d21, x0);
	and (d22, d23, d26);
	or (d23, d21, d24);
	or (d24, d14, d25);
	or (d25, x2, d10);
	and (d26, d27, d28);
	or (d27, d18, d21);
	or (d28, d21, d29);
	or (d29, d9, d14);
	assign f1 = d30;
	and (d30, d31, d32);
	or (d31, x0, d24);
	and (d32, d33, d34);
	or (d33, x0, d29);
	and (d34, d35, d37);
	or (d35, d21, d36);
	or (d36, x1, d25);
	and (d37, d20, d28);
	assign f2 = d38;
	and (d38, d39, d40);
	or (d39, x0, d36);
	and (d40, d2, d41);
	and (d41, d12, d42);
	and (d42, d17, d43);
	and (d43, d44, d46);
	or (d44, d21, d45);
	or (d45, x1, d15);
	and (d46, d35, d47);
	and (d47, d48, d49);
	or (d48, d3, d21);
	and (d49, d20, d50);
	and (d50, d51, d52);
	or (d51, d13, d21);
	and (d52, d23, d27);
	assign f3 = d53;
	and (d53, d54, d55);
	or (d54, x0, d45);
	and (d55, d17, d56);
	and (d56, d33, d57);
	and (d57, d35, d58);
	and (d58, d22, d48);
	assign f4 = d59;
	and (d59, d54, d60);
	and (d60, d39, d61);
	and (d61, d2, d62);
	and (d62, d7, d63);
	and (d63, d31, d64);
	and (d64, d33, d65);
	and (d65, d44, d66);
	and (d66, d48, d67);
	and (d67, d20, d68);
	and (d68, d26, d51);
endmodule
