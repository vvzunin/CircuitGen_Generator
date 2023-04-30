
const RandLevel = ({maxElem, maxLevel, setMaxElem, setMaxLevel}) => {
    return (
      <div className="add__base">
        <label>Максимальное количество уровней<input type="number" value={maxLevel} onChange={e => setMaxLevel(e.target.value)} min={0}/></label>
        <label>Максимальное количество элементов<input type="number" value={maxElem} onChange={e => setMaxElem(e.target.value)} min={0}/></label>
      </div>
    )
}

export default RandLevel;