//f0 = (not x0 and not x1 and not x2 and not x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and x3)
//f1 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3)
//f2 = (not x0 and not x1 and not x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and not x2 and x3)
//f3 = (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and x3) or (x0 and not x1 and not x2 and x3) or (x0 and x1 and not x2 and not x3)
//f4 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3)
//f5 = (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
module CCGRTT1831_CNFT(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68, d69, d70, d71, d72, d73, d74;

	assign f0 = d1;
	or (d1, d2, d9);
	and (d2, d3, d4);
	not (d3, x0);
	and (d4, d5, d6);
	not (d5, x1);
	and (d6, d7, d8);
	not (d7, x2);
	not (d8, x3);
	or (d9, d10, d12);
	and (d10, d3, d11);
	and (d11, x1, d6);
	or (d12, d13, d16);
	and (d13, d3, d14);
	and (d14, x1, d15);
	and (d15, x2, d8);
	or (d16, d17, d20);
	and (d17, x0, d18);
	and (d18, d5, d19);
	and (d19, d7, x3);
	or (d20, d21, d24);
	and (d21, x0, d22);
	and (d22, d5, d23);
	and (d23, x2, x3);
	or (d24, d25, d27);
	and (d25, x0, d26);
	and (d26, x1, d19);
	and (d27, x0, d28);
	and (d28, x1, d23);
	assign f1 = d29;
	or (d29, d2, d30);
	or (d30, d31, d32);
	and (d31, d3, d18);
	or (d32, d33, d34);
	and (d33, d3, d22);
	or (d34, d35, d36);
	and (d35, d3, d26);
	or (d36, d37, d38);
	and (d37, d3, d28);
	or (d38, d39, d40);
	and (d39, x0, d4);
	or (d40, d41, d43);
	and (d41, x0, d42);
	and (d42, d5, d15);
	or (d43, d21, d44);
	or (d44, d45, d46);
	and (d45, x0, d11);
	or (d46, d25, d47);
	and (d47, x0, d14);
	assign f2 = d48;
	or (d48, d31, d49);
	or (d49, d10, d50);
	or (d50, d35, d51);
	or (d51, d37, d52);
	or (d52, d39, d53);
	or (d53, d25, d41);
	assign f3 = d54;
	or (d54, d31, d55);
	or (d55, d56, d57);
	and (d56, d3, d42);
	or (d57, d33, d58);
	or (d58, d35, d59);
	or (d59, d17, d45);
	assign f4 = d60;
	or (d60, d2, d61);
	or (d61, d31, d62);
	or (d62, d33, d63);
	or (d63, d10, d64);
	or (d64, d35, d65);
	or (d65, d37, d43);
	assign f5 = d66;
	or (d66, d56, d67);
	or (d67, d35, d68);
	or (d68, d13, d69);
	or (d69, d17, d70);
	or (d70, d41, d71);
	or (d71, d21, d72);
	or (d72, d45, d73);
	or (d73, d25, d74);
	or (d74, d27, d47);
endmodule
