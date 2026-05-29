// WithMainApp.scala
import chisel3._
import chisel3.stage.ChiselStage

class Adder extends Module {
  val io = IO(new Bundle {
    val a = Input(UInt(8.W))
    val b = Input(UInt(8.W))
    val sum = Output(UInt(8.W))
  })
  
  io.sum := io.a + io.b
}

// ЭТО MAIN ОБЪЕКТ
object GenerateAdder extends App {
  println("Generating Adder module...")
  (new ChiselStage).emitVerilog(new Adder())
}