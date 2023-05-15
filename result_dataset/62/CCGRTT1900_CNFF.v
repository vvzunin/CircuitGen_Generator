//f0 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or not x1 or x2 or not x3)
//f1 = (x0 or x1 or not x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f2 = (x0 or x1 or not x2 or x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or x3) and (not x0 or not x1 or not x2 or x3)
//f3 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (not x0 or x1 or x2 or x3) and (not x0 or x1 or x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or x1 or not x2 or not x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f4 = (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or x2 or not x3) and (not x0 or not x1 or not x2 or not x3)
//f5 = (x0 or x1 or x2 or x3) and (x0 or x1 or x2 or not x3) and (x0 or x1 or not x2 or x3) and (x0 or not x1 or x2 or not x3) and (x0 or not x1 or not x2 or x3) and (not x0 or x1 or not x2 or x3) and (not x0 or not x1 or not x2 or x3) and (not x0 or not x1 or not x2 or not x3)
//f6 = (x0 or x1 or not x2 or x3) and (x0 or x1 or not x2 or not x3) and (x0 or not x1 or not x2 or x3) and (x0 or not x1 or not x2 or not x3) and (not x0 or x1 or x2 or not x3) and (not x0 or not x1 or x2 or not x3)
module CCGRTT1900_CNFF(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5, f6
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68, d69, d70;

	assign f0 = d1;
	and (d1, d2, d5);
	or (d2, x0, d3);
	or (d3, x1, d4);
	or (d4, x2, x3);
	and (d5, d6, d10);
	or (d6, x0, d7);
	or (d7, x1, d8);
	or (d8, x2, d9);
	not (d9, x3);
	and (d10, d11, d14);
	or (d11, x0, d12);
	or (d12, d8, d13);
	not (d13, x1);
	and (d14, d15, d19);
	or (d15, x0, d16);
	or (d16, d13, d17);
	or (d17, x3, d18);
	not (d18, x2);
	and (d19, d20, d23);
	or (d20, x0, d21);
	or (d21, d13, d22);
	or (d22, d9, d18);
	and (d23, d24, d26);
	or (d24, d3, d25);
	not (d25, x0);
	and (d26, d27, d28);
	or (d27, d7, d25);
	or (d28, d12, d25);
	assign f1 = d29;
	and (d29, d30, d32);
	or (d30, x0, d31);
	or (d31, x1, d17);
	and (d32, d24, d33);
	and (d33, d27, d34);
	and (d34, d35, d36);
	or (d35, d25, d31);
	and (d36, d37, d39);
	or (d37, d25, d38);
	or (d38, x1, d22);
	and (d39, d28, d40);
	and (d40, d41, d42);
	or (d41, d16, d25);
	or (d42, d21, d25);
	assign f2 = d43;
	and (d43, d30, d44);
	and (d44, d15, d45);
	and (d45, d24, d46);
	and (d46, d27, d47);
	and (d47, d37, d48);
	and (d48, d41, d49);
	or (d49, d25, d50);
	or (d50, d4, d13);
	assign f3 = d51;
	and (d51, d6, d52);
	and (d52, d30, d53);
	and (d53, d32, d54);
	or (d54, x0, d38);
	assign f4 = d55;
	and (d55, d6, d56);
	and (d56, d30, d57);
	and (d57, d11, d58);
	and (d58, d20, d59);
	and (d59, d35, d60);
	and (d60, d28, d42);
	assign f5 = d61;
	and (d61, d2, d62);
	and (d62, d6, d63);
	and (d63, d30, d64);
	and (d64, d11, d65);
	and (d65, d15, d66);
	and (d66, d35, d40);
	assign f6 = d67;
	and (d67, d30, d68);
	and (d68, d54, d69);
	and (d69, d15, d70);
	and (d70, d20, d26);
endmodule
