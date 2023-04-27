import ToggleSwitchFilter from "./ToggleSwitch";

const NumOperations = () => {
    return (
      <>
        <div className="add__truth">
          {/* <Dropdown data={['and', 'nand', 'or', 'not', 'nor', 'buf', 'xor', 'xnor']} />
          <input className='add__empty' type="number" min={0}/> */}
          <label>and<input type="number" min={0}/></label>
          <label>nand<input type="number" min={0}/></label>
          <label>or<input type="number" min={0}/></label>
          <label>not<input type="number" min={0}/></label>
          <label>nor<input type="number" min={0}/></label>
          <label>buf<input type="number" min={0}/></label>
          <label>xor<input type="number" min={0}/></label>
          <label>xnor<input type="number" min={0}/></label>
        </div>
        <div className="add__truth">
          <div className='add__truth-name'>Оставлять пустые выходы</div><ToggleSwitchFilter/>
        </div>
      </>
    )
  }

export default NumOperations;