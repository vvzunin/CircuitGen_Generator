import ToggleSwitchFilter from "./ToggleSwitch";


const NumOperations = ({setLeaveEmptyOut, numAnd, setNumAnd, numNand, setNumNand, numOr, setNumOr, numNot, setNumNot, numNor, setNumNor, numBuf, setNumBuf, numXor, setNumXor, numXnor, setNumXnor}) => {
    return (
      <>
        <div className="add__truth">
          <label>And<input type="number" min={0} value={numAnd} onChange={e => setNumAnd(e.target.value)}/></label>
          <label>Nand<input type="number" min={0} value={numNand} onChange={e => setNumNand(e.target.value)}/></label>
          <label>Or<input type="number" min={0} value={numOr} onChange={e => setNumOr(e.target.value)}/></label>
          <label>Not<input type="number" min={0} value={numNot} onChange={e => setNumNot(e.target.value)}/></label>
          <label>Nor<input type="number" min={0} value={numNor} onChange={e => setNumNor(e.target.value)}/></label>
          <label>Buf<input type="number" min={0} value={numBuf} onChange={e => setNumBuf(e.target.value)}/></label>
          <label>Xor<input type="number" min={0} value={numXor} onChange={e => setNumXor(e.target.value)}/></label>
          <label>Xnor<input type="number" min={0} value={numXnor} onChange={e => setNumXnor(e.target.value)}/></label>
        </div>
        <div className="add__truth">
          <div className='add__truth-name'>Оставлять пустые выходы</div><ToggleSwitchFilter changeParentState={setLeaveEmptyOut}/>
        </div>
      </>
    )
  }

export default NumOperations;