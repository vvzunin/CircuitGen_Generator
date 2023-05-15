//f0 = (not x0 and not x1 and not x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3)
//f1 = (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and not x2 and x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and x2 and not x3)
//f2 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3)
//f3 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3)
//f4 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f5 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f6 = (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and x2 and x3)
module CCGRTT572_CNFT(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3, f4, f5, f6
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56, d57, d58, d59, d60, d61, d62, d63, d64, d65, d66, d67, d68, d69, d70, d71, d72, d73, d74, d75, d76, d77, d78, d79, d80, d81;

	assign f0 = d1;
	or (d1, d2, d8);
	and (d2, d3, d4);
	not (d3, x0);
	and (d4, d5, d6);
	not (d5, x1);
	and (d6, d7, x3);
	not (d7, x2);
	or (d8, d9, d13);
	and (d9, x0, d10);
	and (d10, d5, d11);
	and (d11, d7, d12);
	not (d12, x3);
	or (d13, d14, d15);
	and (d14, x0, d4);
	or (d15, d16, d19);
	and (d16, x0, d17);
	and (d17, d5, d18);
	and (d18, x2, d12);
	or (d19, d20, d22);
	and (d20, x0, d21);
	and (d21, x1, d6);
	and (d22, x0, d23);
	and (d23, x1, d18);
	assign f1 = d24;
	or (d24, d25, d26);
	and (d25, d3, d17);
	or (d26, d27, d28);
	and (d27, d3, d21);
	or (d28, d14, d29);
	or (d29, d30, d33);
	and (d30, x0, d31);
	and (d31, d5, d32);
	and (d32, x2, x3);
	or (d33, d22, d34);
	and (d34, x0, d35);
	and (d35, x1, d11);
	assign f2 = d36;
	or (d36, d37, d38);
	and (d37, d3, d10);
	or (d38, d2, d39);
	or (d39, d25, d40);
	or (d40, d41, d42);
	and (d41, d3, d31);
	or (d42, d43, d44);
	and (d43, d3, d35);
	or (d44, d27, d45);
	or (d45, d46, d47);
	and (d46, d3, d23);
	or (d47, d48, d50);
	and (d48, d3, d49);
	and (d49, x1, d32);
	or (d50, d14, d51);
	or (d51, d16, d52);
	or (d52, d30, d34);
	assign f3 = d53;
	or (d53, d37, d54);
	or (d54, d41, d55);
	or (d55, d27, d56);
	or (d56, d46, d57);
	or (d57, d9, d19);
	assign f4 = d58;
	or (d58, d37, d59);
	or (d59, d25, d60);
	or (d60, d43, d61);
	or (d61, d46, d62);
	or (d62, d9, d63);
	or (d63, d14, d64);
	or (d64, d30, d65);
	or (d65, d34, d66);
	or (d66, d20, d67);
	or (d67, d22, d68);
	and (d68, x0, d49);
	assign f5 = d69;
	or (d69, d37, d70);
	or (d70, d2, d71);
	or (d71, d25, d72);
	or (d72, d41, d73);
	or (d73, d48, d74);
	or (d74, d30, d75);
	or (d75, d34, d67);
	assign f6 = d76;
	or (d76, d25, d77);
	or (d77, d41, d78);
	or (d78, d43, d79);
	or (d79, d27, d80);
	or (d80, d14, d81);
	or (d81, d30, d68);
endmodule
