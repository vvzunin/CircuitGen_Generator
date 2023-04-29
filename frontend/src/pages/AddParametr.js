import React from 'react'
import { Link } from 'react-router-dom'
import axios from 'axios';
import Dropdown from '../components/Dropdown';
import TruthTable from '../components/TruthTable';
import RandLevel from '../components/RandLevel';
import NumOperations from '../components/NumOperations';  

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
        return <div key={i} className={activeSubmenu === i ? "add__genetic-submenu-item active" : "add__genetic-submenu-item"} onClick={() => setActiveSubmenu(i)}>{item}</div>
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

  const AddParametr = () => {
    let sendData = {};
    sendData.type_of_generation = data[generationMethod];
    sendData.min_in = minInCount;
    sendData.max_in = maxInCount;
    sendData.min_out = minOutCount;
    sendData.max_out = maxOutCount;
    sendData.repeat_n = repeats;
    sendData.limit = limit;
    sendData.CNFF = CNFF;
    sendData.CNFT = CNFT;
    sendData.max_level = maxLevel;
    sendData.max_elem = maxElem;

    sendData.oper_type = "and";
    sendData.chromosome_type = "Truth Table";
    sendData.selection_type_parent = "Panmixia";
    sendData.playback_type = "CrossingEachExit";
    sendData.mut_type = "Binary";
    sendData.selection_type = "Base";

    console.log(sendData);
    
    axios.post('http://127.0.0.1:8000/api/add_parameter/', sendData)
    .then(() => {
      alert('Параметр успешно создан')
    }).catch(e => console.log(e));
  }

  const [generationMethod, setGenerationMethod] = React.useState(0);

  const [minInCount, setMinInCount] = React.useState(0);
  const [maxInCount, setMaxInCount] = React.useState(0);
  const [minOutCount, setMinOutCount] = React.useState(0);
  const [maxOutCount, setMaxOutCount] = React.useState(0);
  const [repeats, setRepeats] = React.useState(0);
  const [limit, setLimit] = React.useState(false);
  const [CNFF, setCNFF] = React.useState(false);
  const [CNFT, setCNFT] = React.useState(false);
  const [maxLevel, setMaxLevel] = React.useState(0);
  const [maxElem, setMaxElem] = React.useState(0);

  return (
    <div className="add__wrapper">
        <div className="add__top">
            <h3>Добавить параметр генерации</h3>
            <div className="add__buttons">
                <button className="add__add" onClick={() => AddParametr()}>Добавить</button>
                <Link to='/' className="add__return">Вернуться на главную</Link>
            </div>
        </div>
        <div className="add__content">
          <div className="add__method">
            <div className="add__method-name">Метод генерации</div>
            <ul>
              {data.map((item, i) => {
                return <li key={i} className={i === generationMethod ? "active" : ""} onClick={() => setGenerationMethod(i)}>{item}</li>
              })}
            </ul>
          </div>
          <div className="add__base">
              {/* {base.map(({name, count}) => {
                return <label>{name}<input type="number" min={0}/></label>
              })} */}
              <label>Минимальное количество входов<input type="number" value={minInCount} onChange={e => setMinInCount(e.target.value)} min={0}/></label>
              <label>Максимальное количество входов<input type="number" value={maxInCount} onChange={e => setMaxInCount(e.target.value)} min={0}/></label>
              <label>Минимальное количество выходов<input type="number" value={minOutCount} onChange={e => setMinOutCount(e.target.value)} min={0}/></label>
              <label>Максимальное количество выходов<input type="number" value={maxOutCount} onChange={e => setMaxOutCount(e.target.value)} min={0}/></label>
              <label>Количество повторений каждой комбинации<input type="number" value={repeats} onChange={e => setRepeats(e.target.value)} min={0}/></label>
          </div>
          {generationMethod === 0 && <TruthTable setLimitParent={setLimit} setCNFFParent={setCNFF} setCNFTParent={setCNFT}/>}
          {generationMethod === 1 && <RandLevel setMaxLevel={setMaxLevel} maxLevel={maxLevel} maxElem={maxElem} setMaxElem={setMaxElem}/>}
          {generationMethod === 2 && <NumOperations/>}
          {generationMethod === 3 && <Genetic/>}
        </div>
    </div>
  )
}

export default AddParametr