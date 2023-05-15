//f0 = (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and not x2 and x3) or (x0 and x1 and not x2 and x3)
//f1 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and x2 and not x3)
//f2 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and x2 and not x3) or (not x0 and not x1 and x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and x1 and x2 and x3)
//f3 = (not x0 and not x1 and not x2 and not x3) or (not x0 and not x1 and x2 and x3) or (not x0 and x1 and not x2 and not x3) or (not x0 and x1 and x2 and x3) or (x0 and not x1 and not x2 and x3) or (x0 and not x1 and x2 and not x3) or (x0 and not x1 and x2 and x3) or (x0 and x1 and not x2 and not x3) or (x0 and x1 and x2 and not x3)
module CCGRTT1659_CNFT(
	input x0, x1, x2, x3,
	output f0, f1, f2, f3
);

	wire d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32, d33, d34, d35, d36, d37, d38, d39, d40, d41, d42, d43, d44, d45, d46, d47, d48, d49, d50;

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
	and (d15, d7, d16);
	not (d16, x2);
	or (d17, d18, d21);
	and (d18, d3, d19);
	and (d19, x1, d20);
	and (d20, x3, d16);
	and (d21, x0, d19);
	assign f1 = d22;
	or (d22, d23, d25);
	and (d23, d3, d24);
	and (d24, d5, d15);
	or (d25, d9, d26);
	or (d26, d27, d29);
	and (d27, d3, d28);
	and (d28, x1, d11);
	or (d29, d30, d32);
	and (d30, x0, d31);
	and (d31, d5, d20);
	or (d32, d33, d34);
	and (d33, x0, d4);
	and (d34, x0, d35);
	and (d35, x1, d6);
	assign f2 = d36;
	or (d36, d23, d37);
	or (d37, d2, d38);
	or (d38, d9, d39);
	or (d39, d33, d40);
	and (d40, x0, d28);
	assign f3 = d41;
	or (d41, d23, d42);
	or (d42, d9, d43);
	or (d43, d13, d44);
	or (d44, d27, d45);
	or (d45, d30, d46);
	or (d46, d33, d47);
	or (d47, d48, d49);
	and (d48, x0, d10);
	or (d49, d34, d50);
	and (d50, x0, d14);
endmodule
