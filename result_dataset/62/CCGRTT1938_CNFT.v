//f0 = (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3)
//f1 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f2 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and x2 and not x3)
//f3 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and x2 and x3)
//f4 = (not x0 and not x1 and x2 and x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3)
//f5 = (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and x2 and not x3)
//f6 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and x1 and x2 and x3)
module CCGRTT1938_CNFT(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5, f6
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68, d69, d70, d71, d72, d73, d74, d75, d76, d77, d78, d79, d80;

	assign f0 = d1;
	or (d1, d2, d8);
	and (d2, d3, d4);
	not (d3, x0);
	and (d4, x1, d5);
	and (d5, d6, d7);
	not (d6, x2);
	not (d7, x3);
	or (d8, d9, d12);
	and (d9, d3, d10);
	and (d10, x1, d11);
	and (d11, d6, x3);
	or (d12, d13, d16);
	and (d13, d3, d14);
	and (d14, x1, d15);
	and (d15, x2, x3);
	or (d16, d17, d20);
	and (d17, x0, d18);
	and (d18, d5, d19);
	not (d19, x1);
	or (d20, d21, d23);
	and (d21, x0, d22);
	and (d22, d15, d19);
	or (d23, d24, d25);
	and (d24, x0, d4);
	or (d25, d26, d27);
	and (d26, x0, d10);
	and (d27, x0, d28);
	and (d28, x1, d29);
	and (d29, x2, d7);
	assign f1 = d30;
	or (d30, d31, d32);
	and (d31, d3, d18);
	or (d32, d33, d35);
	and (d33, d3, d34);
	and (d34, d11, d19);
	or (d35, d36, d37);
	and (d36, d3, d22);
	or (d37, d2, d38);
	or (d38, d9, d39);
	or (d39, d40, d41);
	and (d40, d3, d28);
	or (d41, d17, d42);
	or (d42, d43, d44);
	and (d43, x0, d34);
	or (d44, d21, d45);
	or (d45, d24, d46);
	or (d46, d26, d47);
	or (d47, d27, d48);
	and (d48, x0, d14);
	assign f2 = d49;
	or (d49, d31, d50);
	or (d50, d33, d51);
	or (d51, d52, d54);
	and (d52, d3, d53);
	and (d53, d19, d29);
	or (d54, d36, d55);
	or (d55, d2, d56);
	or (d56, d9, d57);
	or (d57, d13, d58);
	or (d58, d24, d27);
	assign f3 = d59;
	or (d59, d31, d60);
	or (d60, d33, d61);
	or (d61, d52, d62);
	or (d62, d36, d63);
	or (d63, d2, d64);
	or (d64, d17, d65);
	or (d65, d43, d66);
	or (d66, d21, d48);
	assign f4 = d67;
	or (d67, d36, d68);
	or (d68, d13, d69);
	or (d69, d17, d70);
	or (d70, d43, d71);
	or (d71, d72, d73);
	and (d72, x0, d53);
	or (d73, d24, d26);
	assign f5 = d74;
	or (d74, d36, d75);
	or (d75, d2, d76);
	or (d76, d27, d72);
	assign f6 = d77;
	or (d77, d31, d78);
	or (d78, d52, d79);
	or (d79, d2, d80);
	or (d80, d13, d48);
endmodule
