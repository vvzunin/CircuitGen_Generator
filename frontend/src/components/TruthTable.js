import ToggleSwitchFilter from "./ToggleSwitch";

const TruthTable = ({setLimitParent, setCNFFParent, setCNFTParent}) => {

    const changeLimit = (limit) => {
      setLimitParent(limit);
    }
  
    const changeCNFF = (CNFF) => {
      setCNFFParent(CNFF);
    }
  
    const changeCNFT = (CNFT) => {
      setCNFTParent(CNFT);
    }
  
    return (
      <div className="add__truth">
        <div className='add__truth-name'>Ограничение генерации</div><ToggleSwitchFilter changeParentState={(limit) => changeLimit(limit)}/>
        <div className='add__truth-name'>CNFF</div><ToggleSwitchFilter changeParentState={(CNFF) => changeCNFF(CNFF)}/>
        <div className='add__truth-name'>CNFT</div><ToggleSwitchFilter changeParentState={(CNFT) => changeCNFT(CNFT)}/>
      </div>
    )
}

export default TruthTable;