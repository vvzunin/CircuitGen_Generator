import React from 'react'
import { Link } from 'react-router-dom'
import Dropdown from '../components/Dropdown';
import ToggleSwitchFilter from '../components/ToggleSwitch';

const data = ['From Random Truth Table','Rand Level','Num Operation','Genetic'];

const base = [
  {
    name: 'Минимальное количество входов',
    count: 2
  },
  {
    name: 'Максимальное количество входов',
    count: 2
  },
  {
    name: 'Минимальное количество выходов',
    count: 2
  },
  {
    name: 'Максимальное количество выходов',
    count: 2
  },
  {
    name: 'Количество повторений каждой комбинации',
    count: 2
  },
];

const TruthTable = () => {
  return (
    <div className="add__truth">
      <div className='add__truth-name'>Ограничение генерации</div><ToggleSwitchFilter/>
      <div className='add__truth-name'>CNFF</div><ToggleSwitchFilter/>
      <div className='add__truth-name'>CNFT</div><ToggleSwitchFilter/>
    </div>
  )
}

const RandLevel = () => {
  return (
    <div className="add__base">
      <label>Максимальное количество уровней<input type="number"/></label>
      <label>Максимальное количество элементов<input type="number"/></label>
    </div>
  )
}

const NumOperations = () => {
  return (
    <div className="add__truth">
      <div className='add__truth-name'>Оставлять пустые выходы</div><ToggleSwitchFilter/>
      <Dropdown data={['and', 'nand', 'or', 'not', 'nor', 'buf', 'xor', 'xnor']} />
      <input className='add__empty' type="number" min={0}/>
    </div>
  )
}

const Genetic = () => {

  const [activeSubmenu, setActiveSubmenu] = React.useState(0);

  const data = ['Воиспроизведение', 'Мутация', 'Отбор'];

  return (
    <>
    <div className="add__genetic">
      <label>Размер популяции<input type="number"/></label>
      <label>Количество циклов<input type="number"/></label>
      <label>Коэффициент выхода<input type="number"/></label>
      <div className='add__genetic-dropdown'><p>Тип хромосомы</p><Dropdown data={['Truth Table', 'Table 2']}/></div>
    </div>
    <div className="add__genetic-submenu">
      {data.map((item, i) => {
        return <div className={activeSubmenu === i ? "add__genetic-submenu-item active" : "add__genetic-submenu-item"} onClick={() => setActiveSubmenu(i)}>{item}</div>
      })}
    </div>
    {activeSubmenu === 0 && 
      <div className="add__base">
        <div className='add__genetic-dropdown' style={{marginRight: '20px'}}><p>Тип отбора родителей</p><Dropdown data={['Panmixia', 'Inbriding', 'Otbriding', 'Toumament', 'Roulette']}/></div>
        <label>Размер турнира<input type="number"/></label>
        <div className='add__genetic-dropdown' style={{marginRight: '20px'}}><p>Тип воиспроизведения</p><Dropdown data={['CrossingEachExit', 'CrossingUniform', 'CrossingTriadic', 'CrossingReducedReplace', 'CrossingSnuffling']}/></div>
        <label>Reference points<input type="number"/></label>
        <label>maskProbability<input type="number"/></label>
        <label>recombinationNumber<input type="number"/></label>      
      </div>
    }
    {activeSubmenu === 1 && 
      <div className="add__base">
        <div className='add__genetic-dropdown' style={{marginRight: '20px'}}><p>Тип мутации</p><Dropdown data={['Binary', 'Density', 'AccessionDel', 'IncertDel', 'Exchange', 'Delete']}/></div>
        <label>Вероятность мутации<input type="number"/></label>
        <label>Тип обмена<input type="number"/></label>
        <label>Соотношение в таблице истинности<input type="number"/></label>
      </div>
    }
    {activeSubmenu === 2 && 
      <div className="add__base">
        <div className='add__genetic-dropdown' style={{marginRight: '20px'}}><p>Тип отбора</p><Dropdown data={['Base', 'Base 2']}/></div>
        <label>Количество выживших<input type="number"/></label>
      </div>
    }
    </>
  )
}

const AddParametr = () => {

  const [generationMethod, setGenerationMethod] = React.useState(0);

  return (
    <div className="add__wrapper">
        <div className="add__top">
            <h3>Добавить параметр генерации</h3>
            <div className="add__buttons">
                <button className="add__add">Добавить</button>
                <Link to='/' className="add__return">Вернуться на главную</Link>
            </div>
        </div>
        <div className="add__content">
          <div className="add__method">
            <div className="add__method-name">Метод генерации</div>
            <ul>
              {data.map((item, i) => {
                return <li className={i === generationMethod ? "active" : ""} onClick={() => setGenerationMethod(i)}>{item}</li>
              })}
            </ul>
          </div>
          <div className="add__base">
              {base.map(({name, count}) => {
                return <label>{name}<input type="number" min={0}/></label>
              })}
          </div>
          {generationMethod === 0 && <TruthTable/>}
          {generationMethod === 1 && <RandLevel/>}
          {generationMethod === 2 && <NumOperations/>}
          {generationMethod === 3 && <Genetic/>}
        </div>
    </div>
  )
}

export default AddParametr