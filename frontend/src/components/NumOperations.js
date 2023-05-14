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
        </div>
        <div className="add__truth">
          <div className='add__truth-name'>Оставлять пустые выходы</div><ToggleSwitchFilter isChecked={state.leaveEmptyOut} changeParentState={(value) => updateState('leaveEmptyOut', value)}/>
        </div>
      </>
    )
  }

export default NumOperations;