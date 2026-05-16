import chisel3._
import chisel3.stage.ChiselStage

class NandGate extends Module {
  val io = IO(new Bundle {
    val a = Input(Bool())
    val b = Input(Bool())
    val out = Output(Bool())
  })
  io.out := ~(io.a & io.b)
}

class NorGate extends Module {
  val io = IO(new Bundle {
    val a = Input(Bool())
    val b = Input(Bool())
    val out = Output(Bool())
  })
  io.out := ~(io.a | io.b)
}

object Main extends App {
  // Генерация нескольких модулей
  (new ChiselStage).emitVerilog(new NandGate(),
    Array("--target-dir", "generated/nand"))
  
  (new ChiselStage).emitVerilog(new NorGate(),
    Array("--target-dir", "generated/nor"))
}