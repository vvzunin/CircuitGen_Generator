module moduleName (
  ports, f
);
  input ports;
  output f;

  assign f = ~ports;
endmodule