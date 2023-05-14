import Dropdown from "./Dropdown";
import TextField from "./TextField";

const Genetic = ({geneticActive, updateState}) => {

    const data = ['Воиспроизведение', 'Мутация', 'Отбор'];
    
    return (
      <>
      <div className="add__genetic">
        <TextField 
            label="Размер популяции"
            type="number"
            name="population"
            min={1}
          />
          <TextField 
            label="Количество циклов"
            type="number"
            name="cycles"
            min={1}
          />
          <TextField 
            label="Коэффициент выхода"
            type="number"
            name="uOut"
            min={0}
            max={1}
            step={0.01}
          />
        <div className='add__genetic-dropdown'><p>Тип хромосомы</p><Dropdown setActiveParentValue={(value) => updateState("chromosomeType",value)} data={['Truth Table', 'Other']}/></div>
      </div>
      <div className="add__genetic-submenu">
        {data.map((item, i) => {
          return <div key={i} className={geneticActive === i ? "add__genetic-submenu-item active" : "add__genetic-submenu-item"} onClick={() => updateState("geneticActive", i)}>{item}</div>
        })}
      </div>
      {geneticActive === 0 && 
        <div className="add__base">
          <div className='add__genetic-dropdown' style={{marginRight: '20px'}}><p>Тип отбора родителей</p><Dropdown setActiveParentValue={(value) => updateState("selectionTypeParent",value)} data={['Panmixia', 'Inbriding', 'Otbriding', 'Tournament', 'Roulette']}/></div>
          <TextField 
            label="Размер турнира"
            type="number"
            name="tourSize"
            min={1}
          />
          <div className='add__genetic-dropdown' style={{marginRight: '20px'}}><p>Тип воиспроизведения</p><Dropdown setActiveParentValue={(value) => updateState("playbackType",value)} data={['CrossingEachExitInTurnMany', 'CrossingUniform', 'CrossingTriadic', 'CrossingReducedReplace', 'CrossingSnuffling']}/></div>
          <TextField 
            label="Reference points"
            type="number"
            name="refPoints"
            min={0}
          />
          <TextField 
            label="maskProbability"
            type="number"
            name="maskProb"
            min={0}
            max={1}
            step={0.01}
          />
          <TextField 
            label="recombinationNumber"
            type="number"
            name="recNum"
            min={0}
          />
        </div>  
      }
      {geneticActive === 1 && 
        <div className="add__base">
          <div className='add__genetic-dropdown' style={{marginRight: '20px'}}><p>Тип мутации</p><Dropdown setActiveParentValue={(value) => updateState("mutType",value)} data={['Binary', 'Density', 'AccessionDel', 'IncertDel', 'Exchange', 'Delete']}/></div>
          <TextField 
            label="Вероятность мутации"
            type="number"
            name="mutChance"
            min={0}
            max={1}
            step={0.01}
          />
          <div className='add__genetic-dropdown'><p>Тип обмена</p><Dropdown setActiveParentValue={(value) => updateState("swapType",value)} data={['1', '2', '3', '4']}/></div>
          <TextField 
            label="Соотношение в таблице истинности"
            type="number"
            name="ratio"
            min={0}
            max={1}
            step={0.01}
          />
        </div>
      }
      {geneticActive === 2 && 
        <div className="add__base">
          <div className='add__genetic-dropdown' style={{marginRight: '20px'}}><p>Тип отбора</p><Dropdown setActiveParentValue={(value) => updateState("selectionType",value)} data={['Base', 'Other']}/></div>
          <TextField 
            label="Количество выживших"
            type="number"
            name="survNum"
            min={1}
          />
        </div>
      }
      </>
    )
  }

  export default Genetic