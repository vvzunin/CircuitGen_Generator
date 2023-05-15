//f0 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and x3)
//f1 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and x3)
//f2 = (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3)
//f3 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and x3)
//f4 = (not x0 and x1 and not x2 and x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f5 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and x3)
//f6 = (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and x3)
module CCGRTT1901_CNFT(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5, f6
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68, d69, d70, d71, d72, d73, d74, d75, d76, d77, d78, d79, d80, d81, d82;

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
	or (d13, d14, d16);
	and (d14, d3, d15);
	and (d15, x1, d6);
	or (d16, d17, d20);
	and (d17, d3, d18);
	and (d18, x1, d19);
	and (d19, d7, x3);
	or (d20, d21, d23);
	and (d21, d3, d22);
	and (d22, x1, d12);
	or (d23, d24, d27);
	and (d24, d3, d25);
	and (d25, x1, d26);
	and (d26, x2, x3);
	or (d27, d28, d29);
	and (d28, x0, d4);
	or (d29, d30, d32);
	and (d30, x0, d31);
	and (d31, d5, d19);
	or (d32, d33, d35);
	and (d33, x0, d34);
	and (d34, d5, d26);
	and (d35, x0, d18);
	assign f1 = d36;
	or (d36, d2, d37);
	or (d37, d38, d39);
	and (d38, d3, d31);
	or (d39, d10, d40);
	or (d40, d41, d42);
	and (d41, d3, d34);
	or (d42, d14, d43);
	or (d43, d17, d44);
	or (d44, d21, d45);
	or (d45, d46, d47);
	and (d46, x0, d11);
	or (d47, d33, d48);
	or (d48, d35, d49);
	and (d49, x0, d25);
	assign f2 = d50;
	or (d50, d38, d51);
	or (d51, d10, d52);
	or (d52, d41, d53);
	or (d53, d14, d54);
	or (d54, d17, d55);
	or (d55, d33, d56);
	and (d56, x0, d15);
	assign f3 = d57;
	or (d57, d2, d58);
	or (d58, d10, d59);
	or (d59, d41, d60);
	or (d60, d14, d61);
	or (d61, d17, d62);
	or (d62, d21, d63);
	or (d63, d28, d45);
	assign f4 = d64;
	or (d64, d17, d65);
	or (d65, d30, d66);
	or (d66, d33, d67);
	or (d67, d56, d68);
	or (d68, d35, d69);
	or (d69, d49, d70);
	and (d70, x0, d22);
	assign f5 = d71;
	or (d71, d2, d72);
	or (d72, d38, d73);
	or (d73, d41, d74);
	or (d74, d14, d75);
	or (d75, d24, d48);
	assign f6 = d76;
	or (d76, d38, d77);
	or (d77, d10, d78);
	or (d78, d21, d79);
	or (d79, d24, d80);
	or (d80, d28, d81);
	or (d81, d30, d82);
	or (d82, d46, d48);
endmodule
