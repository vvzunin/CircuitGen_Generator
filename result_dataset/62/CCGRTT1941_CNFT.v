//f0 = (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f1 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and x2 and not x3)
//f2 = (not x0 and not x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and x2 and x3)
//f3 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and x2 and not x3)
//f4 = (not x0 and not x1 and x2 and x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and not x2 and not x3)
//f5 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and x2 and x3)
//f6 = (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
module CCGRTT1941_CNFT(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5, f6
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68, d69, d70, d71, d72, d73, d74, d75, d76, d77, d78, d79;

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
	and (d10, d5, d11);
	and (d11, x2, d12);
	not (d12, x3);
	or (d13, d14, d17);
	and (d14, d3, d15);
	and (d15, d5, d16);
	and (d16, x2, x3);
	or (d17, d18, d20);
	and (d18, d3, d19);
	and (d19, x1, d6);
	or (d20, d21, d23);
	and (d21, d3, d22);
	and (d22, x1, d11);
	or (d23, d24, d27);
	and (d24, x0, d25);
	and (d25, d5, d26);
	and (d26, d7, d12);
	or (d27, d28, d29);
	and (d28, x0, d4);
	or (d29, d30, d32);
	and (d30, x0, d31);
	and (d31, x1, d26);
	or (d32, d33, d34);
	and (d33, x0, d22);
	and (d34, x0, d35);
	and (d35, x1, d16);
	assign f1 = d36;
	or (d36, d37, d38);
	and (d37, d3, d25);
	or (d38, d9, d39);
	or (d39, d14, d40);
	or (d40, d18, d41);
	or (d41, d42, d43);
	and (d42, d3, d35);
	or (d43, d24, d44);
	or (d44, d45, d46);
	and (d45, x0, d15);
	or (d46, d30, d33);
	assign f2 = d47;
	or (d47, d37, d48);
	or (d48, d18, d49);
	or (d49, d45, d50);
	or (d50, d30, d34);
	assign f3 = d51;
	or (d51, d37, d52);
	or (d52, d9, d53);
	or (d53, d54, d55);
	and (d54, d3, d31);
	or (d55, d21, d56);
	or (d56, d42, d57);
	or (d57, d33, d58);
	and (d58, x0, d10);
	assign f4 = d59;
	or (d59, d14, d60);
	or (d60, d42, d61);
	or (d61, d24, d62);
	or (d62, d30, d58);
	assign f5 = d63;
	or (d63, d37, d64);
	or (d64, d2, d65);
	or (d65, d9, d66);
	or (d66, d14, d67);
	or (d67, d28, d68);
	or (d68, d34, d45);
	assign f6 = d69;
	or (d69, d2, d70);
	or (d70, d9, d71);
	or (d71, d54, d72);
	or (d72, d18, d73);
	or (d73, d24, d74);
	or (d74, d28, d75);
	or (d75, d58, d76);
	or (d76, d45, d77);
	or (d77, d30, d78);
	or (d78, d32, d79);
	and (d79, x0, d19);
endmodule
