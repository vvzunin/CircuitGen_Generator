import chisel3._

class SimpleCounter extends Module {
  val io = IO(new Bundle {
    val en = Input(Bool())
    val out = Output(UInt(8.W))
  })
  
  val counter = RegInit(0.U(8.W))
  when(io.en) {
    counter := counter + 1.U
  }
  io.out := counter
}

class SimpleAdder extends Module {
  val io = IO(new Bundle {
    val a = Input(UInt(8.W))
    val b = Input(UInt(8.W))
    val sum = Output(UInt(8.W))
  })
  
  io.sum := io.a + io.b
}