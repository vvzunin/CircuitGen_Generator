import chisel3._
import chisel3.stage.ChiselStage

class ParameterizedALU(val width: Int = 8, val useCarry: Boolean = true) extends Module {
  val io = IO(new Bundle {
    val a = Input(UInt(width.W))
    val b = Input(UInt(width.W))
    val op = Input(UInt(3.W))
    val result = Output(UInt(width.W))
  })
  
  io.result := MuxLookup(io.op, 0.U)(
    Seq(
      0.U -> (io.a + io.b),
      1.U -> (io.a - io.b),
      2.U -> (io.a & io.b),
      3.U -> (io.a | io.b)
    )
  )
}

object Main extends App {
  (new ChiselStage).emitVerilog(new ParameterizedALU())
}