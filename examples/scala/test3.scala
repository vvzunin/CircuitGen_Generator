import chisel3._
import chisel3.stage.ChiselStage

class OrGate extends Module {
  val io = IO(new Bundle {
    val a = Input(Bool())
    val b = Input(Bool())
    val out = Output(Bool())
  })
  io.out := io.a | io.b
}

object Main {
  def main(args: Array[String]): Unit = {
    (new ChiselStage).emitVerilog(new OrGate(),
      Array("--target-dir", "generated"))
  }
}