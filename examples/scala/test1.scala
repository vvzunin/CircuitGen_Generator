// SimpleModule.scala
import chisel3._

class AndGate extends Module {
  val io = IO(new Bundle {
    val a = Input(UInt(1.W))
    val b = Input(UInt(1.W))
    val c = Output(UInt(1.W))
  })
  
  io.c := io.a & io.b
}

class OrGate extends Module {
  val io = IO(new Bundle {
    val a = Input(Bool())
    val b = Input(Bool())
    val c = Output(Bool())
  })
  
  io.c := io.a | io.b
}