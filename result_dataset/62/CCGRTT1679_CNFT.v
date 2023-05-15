//f0 = (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3)
//f1 = (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and x2 and not x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and not x2 and x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f2 = (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and x3)
//f3 = (not x0 and not x1 and not x2 and x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and not x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
module CCGRTT1679_CNFT(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50, d51, d52, d53, d54, d55, d56;

	assign f0 = d1;
	or (d1, d2, d8);
	and (d2, d3, d4);
	not (d3, x0);
	and (d4, d5, d6);
	not (d5, x1);
	and (d6, d7, x3);
	not (d7, x2);
	or (d8, d9, d12);
	and (d9, d3, d10);
	and (d10, d5, d11);
	and (d11, x2, x3);
	or (d12, d13, d15);
	and (d13, d3, d14);
	and (d14, x1, d11);
	or (d15, d16, d17);
	and (d16, x0, d10);
	or (d17, d18, d20);
	and (d18, x0, d19);
	and (d19, x1, d6);
	and (d20, x0, d21);
	and (d21, x1, d22);
	and (d22, x2, d23);
	not (d23, x3);
	assign f1 = d24;
	or (d24, d2, d25);
	or (d25, d9, d26);
	or (d26, d27, d28);
	and (d27, d3, d21);
	or (d28, d29, d31);
	and (d29, x0, d30);
	and (d30, d5, d22);
	or (d31, d32, d35);
	and (d32, x0, d33);
	and (d33, x1, d34);
	and (d34, d7, d23);
	or (d35, d18, d36);
	or (d36, d20, d37);
	and (d37, x0, d14);
	assign f2 = d38;
	or (d38, d9, d39);
	or (d39, d40, d41);
	and (d40, d3, d33);
	or (d41, d42, d43);
	and (d42, d3, d19);
	or (d43, d27, d44);
	or (d44, d13, d45);
	or (d45, d16, d18);
	assign f3 = d46;
	or (d46, d2, d47);
	or (d47, d48, d49);
	and (d48, d3, d30);
	or (d49, d40, d50);
	or (d50, d27, d51);
	or (d51, d13, d52);
	or (d52, d53, d55);
	and (d53, x0, d54);
	and (d54, d5, d34);
	or (d55, d29, d56);
	or (d56, d16, d36);
endmodule
