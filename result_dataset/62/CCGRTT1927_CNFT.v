//f0 = (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3)
//f1 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3)
//f2 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3)
//f3 = (not x0 and x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f4 = (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3)
//f5 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and x2 and not x3)
//f6 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and x3)
module CCGRTT1927_CNFT(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5, f6
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68, d69, d70, d71, d72, d73, d74, d75, d76, d77, d78, d79, d80, d81, d82, d83;

	assign f0 = d1;
	or (d1, d2, d8);
	and (d2, d3, d4);
	not (d3, x0);
	and (d4, d5, d6);
	not (d5, x1);
	and (d6, x2, d7);
	not (d7, x3);
	or (d8, d9, d12);
	and (d9, d3, d10);
	and (d10, d5, d11);
	and (d11, x2, x3);
	or (d12, d13, d17);
	and (d13, d3, d14);
	and (d14, x1, d15);
	and (d15, x3, d16);
	not (d16, x2);
	or (d17, d18, d20);
	and (d18, d3, d19);
	and (d19, x1, d6);
	or (d20, d21, d22);
	and (d21, x0, d10);
	and (d22, x0, d23);
	and (d23, x1, d24);
	and (d24, d7, d16);
	assign f1 = d25;
	or (d25, d26, d28);
	and (d26, d3, d27);
	and (d27, d5, d24);
	or (d28, d29, d31);
	and (d29, d3, d30);
	and (d30, d5, d15);
	or (d31, d2, d32);
	or (d32, d33, d34);
	and (d33, d3, d23);
	or (d34, d18, d35);
	or (d35, d36, d38);
	and (d36, d3, d37);
	and (d37, x1, d11);
	or (d38, d39, d40);
	and (d39, x0, d27);
	or (d40, d41, d42);
	and (d41, x0, d30);
	or (d42, d21, d43);
	or (d43, d44, d45);
	and (d44, x0, d14);
	and (d45, x0, d19);
	assign f2 = d46;
	or (d46, d26, d47);
	or (d47, d29, d48);
	or (d48, d9, d49);
	or (d49, d13, d50);
	or (d50, d18, d51);
	or (d51, d39, d42);
	assign f3 = d52;
	or (d52, d13, d53);
	or (d53, d54, d55);
	and (d54, x0, d4);
	or (d55, d21, d56);
	or (d56, d44, d57);
	or (d57, d45, d58);
	and (d58, x0, d37);
	assign f4 = d59;
	or (d59, d29, d60);
	or (d60, d9, d61);
	or (d61, d33, d62);
	or (d62, d18, d63);
	or (d63, d36, d64);
	or (d64, d41, d65);
	or (d65, d20, d54);
	assign f5 = d66;
	or (d66, d26, d67);
	or (d67, d29, d68);
	or (d68, d33, d69);
	or (d69, d18, d70);
	or (d70, d39, d71);
	or (d71, d41, d72);
	or (d72, d54, d73);
	or (d73, d21, d45);
	assign f6 = d74;
	or (d74, d26, d75);
	or (d75, d2, d76);
	or (d76, d9, d77);
	or (d77, d13, d78);
	or (d78, d18, d79);
	or (d79, d39, d80);
	or (d80, d54, d81);
	or (d81, d21, d82);
	or (d82, d22, d83);
	or (d83, d44, d58);
endmodule
