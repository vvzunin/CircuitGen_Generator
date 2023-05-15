//f0 = (not x0 and not x1 and not x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3)
//f1 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f2 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3)
//f3 = (not x0 and x1 and not x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and x2 and x3)
//f4 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and x2 and not x3)
//f5 = (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and x2 and x3)
//f6 = (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
module CCGRTT1908_CNFT(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5, f6
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68, d69, d70, d71, d72, d73, d74;

	assign f0 = d1;
	or (d1, d2, d8);
	and (d2, d3, d4);
	not (d3, x0);
	and (d4, d5, d6);
	not (d5, x1);
	and (d6, d7, x3);
	not (d7, x2);
	or (d8, d9, d13);
	and (d9, d3, d10);
	and (d10, x1, d11);
	and (d11, d7, d12);
	not (d12, x3);
	or (d13, d14, d17);
	and (d14, d3, d15);
	and (d15, x1, d16);
	and (d16, x2, x3);
	or (d17, d18, d19);
	and (d18, x0, d4);
	or (d19, d20, d21);
	and (d20, x0, d10);
	or (d21, d22, d24);
	and (d22, x0, d23);
	and (d23, x1, d6);
	and (d24, x0, d25);
	and (d25, x1, d26);
	and (d26, x2, d12);
	assign f1 = d27;
	or (d27, d28, d30);
	and (d28, d3, d29);
	and (d29, d5, d11);
	or (d30, d31, d33);
	and (d31, d3, d32);
	and (d32, d5, d16);
	or (d33, d34, d35);
	and (d34, d3, d23);
	or (d35, d36, d37);
	and (d36, d3, d25);
	or (d37, d14, d38);
	or (d38, d18, d39);
	or (d39, d24, d40);
	and (d40, x0, d15);
	assign f2 = d41;
	or (d41, d28, d42);
	or (d42, d43, d45);
	and (d43, d3, d44);
	and (d44, d5, d26);
	or (d45, d34, d46);
	or (d46, d36, d47);
	or (d47, d21, d48);
	and (d48, x0, d32);
	assign f3 = d49;
	or (d49, d34, d50);
	or (d50, d51, d52);
	and (d51, x0, d29);
	or (d52, d40, d48);
	assign f4 = d53;
	or (d53, d28, d54);
	or (d54, d2, d55);
	or (d55, d31, d56);
	or (d56, d9, d57);
	or (d57, d36, d58);
	or (d58, d14, d59);
	or (d59, d60, d61);
	and (d60, x0, d44);
	or (d61, d48, d62);
	or (d62, d20, d24);
	assign f5 = d63;
	or (d63, d43, d64);
	or (d64, d31, d65);
	or (d65, d51, d66);
	or (d66, d52, d60);
	assign f6 = d67;
	or (d67, d43, d68);
	or (d68, d31, d69);
	or (d69, d34, d70);
	or (d70, d14, d71);
	or (d71, d51, d72);
	or (d72, d18, d73);
	or (d73, d20, d74);
	or (d74, d22, d39);
endmodule
