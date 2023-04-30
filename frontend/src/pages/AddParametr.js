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
        <label>Вероятность мутации<input type="number" min={0} value={mutChance} onChange={e => setMutChance(e.target.value)}/></label>
        <label>Тип обмена<input type="number" min={0} value={swapType} onChange={e => setSwapType(e.target.value)}/></label>
        <label>Соотношение в таблице истинности<input type="number" min={0} value={ratio} onChange={e => setRatio(e.target.value)}/></label>
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

const AddParametr = () => {

  const genetic = ['Genetic reproduction', 'Genetic mutation', 'Genetic selection'];

  const [geneticActive, setGeneticActive] = React.useState(0); 

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
  const [population, setPopulation] = React.useState(0);
  const [cycles, setCycles] = React.useState(0);
  const [uOut, setUOut] = React.useState(0);

  const [tourSize, setTourSize] = React.useState(0);
  const [refPoints, setRefPoints] = React.useState(0);
  const [maskProb, setMaskProb] = React.useState(0);
  const [recNum, setRecNum] = React.useState(0);
  const [mutChance, setMutChance] = React.useState(0);
  const [swapType, setSwapType] = React.useState(0);
  const [ratio, setRatio] = React.useState(0);
  const [survNum, setSurvNum] = React.useState(0);

  const [chromosomeType, setChromosomeType] = React.useState('Truth Table');
  const [selectionTypeParent, setSelectionTypeParent] = React.useState('Panmixia');
  const [playbackType, setPlaybackType] = React.useState('CrossingEachExit');
  const [mutType, setMutType] = React.useState('Binary');
  const [selectionType, setSelectionType] = React.useState('Base');


  const AddParametr = () => {
    let sendData = {};
    if (generationMethod === 3) {
      sendData.type_of_generation = genetic[geneticActive];
    } else {
      sendData.type_of_generation = data[generationMethod];
    }
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
    sendData.population = population;
    sendData.cycles = cycles;
    sendData.u_out = uOut; 
    sendData.tour_size = tourSize;
    sendData.ref_points = refPoints;
    sendData.mask_prob = maskProb;
    sendData.rec_num = recNum;
    sendData.mut_chance = mutChance;
    sendData.swap_type = swapType;
    sendData.ratio = ratio;
    sendData.surv_num = survNum;

    sendData.oper_type = "and";

    sendData.chromosome_type = chromosomeType;
    sendData.selection_type_parent = selectionTypeParent;
    sendData.playback_type = playbackType;
    sendData.mut_type = mutType;
    sendData.selection_type = selectionType;

    console.log(sendData);
    
    axios.post('http://127.0.0.1:8000/api/add_parameter/', sendData)
    .then(() => {
      alert('Параметр успешно создан')
    }).catch(e => console.log(e));
  }

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
          {generationMethod === 3 && <Genetic 
            setMutType={setMutType}
            setSelectionType={setSelectionType}
            setPlaybackType={setPlaybackType}
            setSelectionTypeParent= {setSelectionTypeParent}
            setChromosomeType={setChromosomeType}
            geneticActive={geneticActive} setGeneticActive={setGeneticActive} 
            population={population} setPopulation={setPopulation} 
            cycles={cycles} setCycles={setCycles} 
            uOut={uOut} setUOut={setUOut}
            tourSize={tourSize} setTourSize={setTourSize}
            refPoints={refPoints} setRefPoints={setRefPoints}
            maskProb={maskProb} setMaskProb={setMaskProb}
            recNum={recNum} setRecNum={setRecNum}
            mutChance={mutChance} setMutChance={setMutChance}
            swapType={swapType} setSwapType={setSwapType}
            ratio={ratio} setRatio={setRatio}
            survNum={survNum} setSurvNum={setSurvNum}
          />}
        </div>
    </div>
  )
}


export default AddParametr