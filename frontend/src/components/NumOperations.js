import ToggleSwitchFilter from "./ToggleSwitch";
import TextField from "./TextField";

const NumOperations = ({updateState, state}) => {
    return (
      <>
        <div className="add__truth">
          <TextField 
            label="And"
            type="number"
            name="numAnd"
            min={0}
          />
          <TextField 
            label="Nand"
            type="number"
            name="numNand"
            min={0}
          />
          <TextField 
            label="Or"
            type="number"
            name="numOr"
            min={0}
          />
          <TextField 
            label="Not"
            type="number"
            name="numNot"
            min={0}
          />
          <TextField 
            label="Nor"
            type="number"
            name="numNor"
            min={0}
          />
          <TextField 
            label="Buf"
            type="number"
            name="numBuf"
            min={0}
          />
          <TextField 
            label="Xor"
            type="number"
            name="numXor"
            min={0}
          />
          <TextField 
            label="Xnor"
            type="number"
            name="numXnor"
            min={0}
          />
          {/* <label>And<input type="number" min={0} value={numAnd} onChange={e => setNumAnd(e.target.value)}/></label>
          <label>Nand<input type="number" min={0} value={numNand} onChange={e => setNumNand(e.target.value)}/></label>
          <label>Or<input type="number" min={0} value={numOr} onChange={e => setNumOr(e.target.value)}/></label>
          <label>Not<input type="number" min={0} value={numNot} onChange={e => setNumNot(e.target.value)}/></label>
          <label>Nor<input type="number" min={0} value={numNor} onChange={e => setNumNor(e.target.value)}/></label>
          <label>Buf<input type="number" min={0} value={numBuf} onChange={e => setNumBuf(e.target.value)}/></label>
          <label>Xor<input type="number" min={0} value={numXor} onChange={e => setNumXor(e.target.value)}/></label>
          <label>Xnor<input type="number" min={0} value={numXnor} onChange={e => setNumXnor(e.target.value)}/></label> */}
        </div>
        <div className="add__truth">
          <div className='add__truth-name'>Оставлять пустые выходы</div><ToggleSwitchFilter isChecked={state.leaveEmptyOut} changeParentState={(value) => updateState('leaveEmptyOut', value)}/>
        </div>
      </>
    )
  }

export default NumOperations;