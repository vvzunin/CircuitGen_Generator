//f0 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f1 = (not x0 and not x1 and x2 and x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and x2 and x3)
//f2 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f3 = (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3)
//f4 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f5 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and x2 and x3)
module CCGRTT1838_CNFT(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68, d69, d70, d71, d72, d73, d74, d75, d76, d77, d78;

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
	and (d15, d5, d16);
	and (d16, x2, x3);
	or (d17, d18, d20);
	and (d18, d3, d19);
	and (d19, x1, d6);
	or (d20, d21, d23);
	and (d21, d3, d22);
	and (d22, x1, d12);
	or (d23, d24, d26);
	and (d24, d3, d25);
	and (d25, x1, d16);
	or (d26, d27, d28);
	and (d27, x0, d4);
	or (d28, d29, d32);
	and (d29, x0, d30);
	and (d30, d5, d31);
	and (d31, d7, x3);
	or (d32, d33, d34);
	and (d33, x0, d11);
	or (d34, d35, d36);
	and (d35, x0, d19);
	or (d36, d37, d38);
	and (d37, x0, d22);
	and (d38, x0, d25);
	assign f1 = d39;
	or (d39, d14, d40);
	or (d40, d21, d41);
	or (d41, d27, d42);
	or (d42, d29, d43);
	or (d43, d33, d44);
	or (d44, d35, d38);
	assign f2 = d45;
	or (d45, d2, d46);
	or (d46, d47, d48);
	and (d47, d3, d30);
	or (d48, d14, d49);
	or (d49, d18, d50);
	or (d50, d27, d51);
	or (d51, d33, d36);
	assign f3 = d52;
	or (d52, d47, d53);
	or (d53, d10, d54);
	or (d54, d14, d55);
	or (d55, d18, d56);
	or (d56, d57, d59);
	and (d57, d3, d58);
	and (d58, x1, d31);
	or (d59, d21, d60);
	or (d60, d33, d61);
	or (d61, d37, d62);
	and (d62, x0, d58);
	assign f4 = d63;
	or (d63, d2, d64);
	or (d64, d47, d65);
	or (d65, d10, d66);
	or (d66, d14, d67);
	or (d67, d18, d68);
	or (d68, d21, d69);
	or (d69, d27, d70);
	or (d70, d71, d72);
	and (d71, x0, d15);
	or (d72, d35, d73);
	or (d73, d36, d62);
	assign f5 = d74;
	or (d74, d2, d75);
	or (d75, d10, d76);
	or (d76, d14, d77);
	or (d77, d18, d78);
	or (d78, d40, d57);
endmodule
