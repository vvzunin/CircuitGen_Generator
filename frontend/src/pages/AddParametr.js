import React from 'react'
import { Link } from 'react-router-dom'
import axios from 'axios';
import TruthTable from '../components/TruthTable';
import RandLevel from '../components/RandLevel';
import NumOperations from '../components/NumOperations';
import Genetic from '../components/Genetic';

const data = ['From Random Truth Table','Rand Level','Num Operation','Genetic'];


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

  const [numAnd, setNumAnd] = React.useState(0);
  const [numNand, setNumNand] = React.useState(0);
  const [numOr, setNumOr] = React.useState(0);
  const [numNot, setNumNot] = React.useState(0);
  const [numNor, setNumNor] = React.useState(0);
  const [numBuf, setNumBuf] = React.useState(0);
  const [numXor, setNumXor] = React.useState(0);
  const [numXnor, setNumXnor] = React.useState(0);
  const [leaveEmptyOut, setLeaveEmptyOut] = React.useState(false);


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
    sendData.ratio_in_table = ratio;
    sendData.surv_num = survNum;
    sendData.chromosome_type = chromosomeType;
    sendData.selection_type_parent = selectionTypeParent;
    sendData.playback_type = playbackType;
    sendData.mut_type = mutType;
    sendData.selection_type = selectionType;

    sendData.num_and = numAnd;
    sendData.num_nand = numNand;
    sendData.num_or = numOr;
    sendData.num_not = numNot;
    sendData.num_nor = numNor;
    sendData.num_buf = numBuf;
    sendData.num_xor = numXor;
    sendData.num_xnor = numXnor;
    sendData.leave_empty_out = leaveEmptyOut;;



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
          {generationMethod === 2 && <NumOperations
            setLeaveEmptyOut={setLeaveEmptyOut} 
            numAnd={numAnd} setNumAnd={setNumAnd}
            numNand={numNand} setNumNand={setNumNand}
            numOr={numOr} setNumOr={setNumOr}
            numNot={numNot} setNumNot={setNumNot}
            numNor={numNor} setNumNor={setNumNor}
            numBuf={numBuf} setNumBuf={setNumBuf}
            numXor={numXor} setNumXor={setNumXor}
            numXnor={numXnor} setNumXnor={setNumXnor}
          />}
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