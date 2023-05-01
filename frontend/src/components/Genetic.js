import Dropdown from "./Dropdown";

const Genetic = ({setMutType, setSelectionType, setPlaybackType, setSelectionTypeParent, setChromosomeType, survNum, setSurvNum, ratio, setRatio, swapType, setSwapType, mutChance, setMutChance, recNum, setRecNum, maskProb, setMaskProb, refPoints, setRefPoints, tourSize, setTourSize, population, setPopulation, cycles, setCycles, uOut, setUOut, geneticActive, setGeneticActive}) => {

    const data = ['Воиспроизведение', 'Мутация', 'Отбор'];
  
  
  
    return (
      <>
      <div className="add__genetic">
        <label>Размер популяции<input type="number" min={0} value={population} onChange={e => setPopulation(e.target.value)}/></label>
        <label>Количество циклов<input type="number" min={0} value={cycles} onChange={e => setCycles(e.target.value)}/></label>
        <label>Коэффициент выхода<input type="number" min={0} value={uOut} onChange={e => setUOut(e.target.value)}/></label>
        <div className='add__genetic-dropdown'><p>Тип хромосомы</p><Dropdown setActiveParentValue={setChromosomeType} data={['Truth Table', 'Table 2']}/></div>
      </div>
      <div className="add__genetic-submenu">
        {data.map((item, i) => {
          return <div key={i} className={geneticActive === i ? "add__genetic-submenu-item active" : "add__genetic-submenu-item"} onClick={() => setGeneticActive(i)}>{item}</div>
        })}
      </div>
      {geneticActive === 0 && 
        <div className="add__base">
          <div className='add__genetic-dropdown' style={{marginRight: '20px'}}><p>Тип отбора родителей</p><Dropdown setActiveParentValue={setSelectionTypeParent} data={['Panmixia', 'Inbriding', 'Otbriding', 'Toumament', 'Roulette']}/></div>
          <label>Размер турнира<input type="number" min={0} value={tourSize} onChange={e => setTourSize(e.target.value)}/></label>
          <div className='add__genetic-dropdown' style={{marginRight: '20px'}}><p>Тип воиспроизведения</p><Dropdown setActiveParentValue={setPlaybackType} data={['CrossingEachExit', 'CrossingUniform', 'CrossingTriadic', 'CrossingReducedReplace', 'CrossingSnuffling']}/></div>
          <label>Reference points<input type="number" min={0} value={refPoints} onChange={e => setRefPoints(e.target.value)}/></label>
          <label>maskProbability<input type="number" min={0} value={maskProb} onChange={e => setMaskProb(e.target.value)}/></label>
          <label>recombinationNumber<input type="number" min={0} value={recNum} onChange={e => setRecNum(e.target.value)}/></label>      
        </div>
      }
      {geneticActive === 1 && 
        <div className="add__base">
          <div className='add__genetic-dropdown' style={{marginRight: '20px'}}><p>Тип мутации</p><Dropdown setActiveParentValue={setMutType} data={['Binary', 'Density', 'AccessionDel', 'IncertDel', 'Exchange', 'Delete']}/></div>
          <label>Вероятность мутации<input type="number" min={0} max={1} step={0.01} value={mutChance} onChange={e => setMutChance(e.target.value)}/></label>
          <label>Тип обмена<input type="number" min={0} value={swapType} onChange={e => setSwapType(e.target.value)}/></label>
          <label>Соотношение в таблице истинности<input type="number" min={0} max={1} step={0.01} value={ratio} onChange={e => setRatio(e.target.value)}/></label>
        </div>
      }
      {geneticActive === 2 && 
        <div className="add__base">
          <div className='add__genetic-dropdown' style={{marginRight: '20px'}}><p>Тип отбора</p><Dropdown setActiveParentValue={setSelectionType} data={['Base', 'Base 2']}/></div>
          <label>Количество выживших<input type="number" min={0} value={survNum} onChange={e => setSurvNum(e.target.value)}/></label>
        </div>
      }
      </>
    )
  }

  export default Genetic