import React, { useEffect } from 'react'
import { Link } from 'react-router-dom'
import axios from 'axios';
import { Formik, Form, Field, ErrorMessage, useField } from 'formik';
import * as Yup from 'yup';

import TruthTable from '../components/TruthTable';
import RandLevel from '../components/RandLevel';
import NumOperations from '../components/NumOperations';
import Genetic from '../components/Genetic';
import TextField from '../components/TextField';

import dice from '../assets/dice.svg';

const data = ['From Random Truth Table','Rand Level','Num Operation','Genetic'];
const genetic = ['Genetic reproduction', 'Genetic mutation', 'Genetic selection'];

const INT_MAX = 2147483647;
const UINT_MAX = 4294967295;

const AddParameter = () => {

  const validateNumber = (min, max = INT_MAX) =>
  Yup.number()
    .required()
    .integer()
    .min(min)
    .max(max);

  const validateChance = () =>
  Yup.number()
  .required()
  .min(0)
  .max(1);

  const validate = Yup.object({
    minInCount: validateNumber(1),
    maxInCount: Yup.number()
    .required()
    .integer()
    .min(1)
    .max(INT_MAX)
    .test('greaterThan', 'maxInCount должно быть больше minInCount', function(value) {
      const { minInCount } = this.parent;
      return value >= minInCount;
    }),
    minOutCount: validateNumber(1),
    maxOutCount: Yup.number()
    .required()
    .integer()
    .min(1)
    .max(INT_MAX)
    .test('greaterThan', 'maxOutCount должно быть больше minOutCount', function(value) {
      const { minOutCount } = this.parent;
      return value >= minOutCount;
    }),
    repeats: validateNumber(1),
    seed: validateNumber(-1, UINT_MAX),
    maxElem: validateNumber(1),
    maxLevel: validateNumber(1),
    numAnd: validateNumber(0),
    numNand: validateNumber(0),
    numOr: validateNumber(0),
    numNot: validateNumber(0),
    numNor: validateNumber(0),
    numBuf: validateNumber(0),
    numXor: validateNumber(0),
    numXnor: validateNumber(0),
    population: validateNumber(1),
    cycles: validateNumber(1),
    uOut: validateChance(),
    mutChance: validateChance(),
    ratio: validateChance(),
    survNum: validateNumber(1),
    tourSize: validateNumber(1),
    refPoints: validateNumber(0),
    maskProb: validateChance(),
    recNum: validateNumber(0),
})

  const [check, setCheck] = React.useState(false);

  React.useEffect(() => {
    if (check) {
      addParameter()
      setCheck(false)
    }
  }, [check])

  const [state, setState] = React.useState({
    geneticActive: 0,
    generationMethod: 0,
    minInCount: 1,
    maxInCount: 1,
    minOutCount: 1,
    maxOutCount: 1,
    repeats: 1,
    seed: -1,
    limit: false,
    CNFF: true,
    CNFT: true,
    maxLevel: 1,
    maxElem: 1,
    population: 1,
    cycles: 1,
    uOut: 0,
    tourSize: 1,
    refPoints: 0,
    maskProb: 0,
    recNum: 0,
    mutChance: 0,
    swapType: 0,
    ratio: 0,
    survNum: 1,
    chromosomeType: 'Truth Table',
    selectionTypeParent: 'Panmixia',
    playbackType: 'CrossingEachExitInTurnMany',
    mutType: 'Binary',
    selectionType: 'Base',
    numAnd: 0,
    numNand: 0,
    numOr: 0,
    numNot: 0,
    numNor: 0,
    numBuf: 0,
    numXor: 0,
    numXnor: 0,
    leaveEmptyOut: false,
  });

  const {
    geneticActive,
    generationMethod,
    minInCount,
    maxInCount,
    minOutCount,
    maxOutCount,
    repeats,
    seed,
    CNFF,
    CNFT,
    maxLevel,
    maxElem,
    population,
    cycles,
    uOut,
    tourSize,
    refPoints,
    maskProb,
    recNum,
    mutChance,
    swapType,
    ratio,
    survNum,
    chromosomeType,
    selectionTypeParent,
    playbackType,
    mutType,
    selectionType,
    numAnd,
    numNand,
    numOr,
    numNot,
    numNor,
    numBuf,
    numXor,
    numXnor,
    leaveEmptyOut,
  } = state;
  
  const updateState = (key, value) => {
    setState(prevState => ({
      ...prevState,
      [key]: value,
    }));
  };

  const addParameter = () => {
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
    sendData.seed = seed;
    sendData.CNFF = CNFF;
    sendData.CNFT = CNFT;
    sendData.max_level = maxLevel;
    sendData.max_elem = maxElem;
    sendData.population_size = population;
    sendData.cycles = cycles;
    sendData.out_ratio = uOut; 
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
    sendData.leave_empty_out = leaveEmptyOut;


    console.log(sendData);
    
    axios.post('http://127.0.0.1:8000/api/add_parameter/', sendData)
    .then(() => {
      alert('Параметр успешно создан!')
    }).catch(e => console.log(e));
  }

  return (
    <Formik
      initialValues={{
        minInCount: 1, 
        maxInCount: 1, 
        minOutCount: 1,
        maxOutCount: 1, 
        repeats: 1, 
        seed: -1,
        maxElem: 1, 
        maxLevel: 1,
        numAnd: 0, 
        numNand: 0,
        numOr: 0,
        numNot: 0,
        numNor: 0,
        numBuf: 0,
        numXor: 0,
        numXnor: 0,
        population: 1,
        cycles: 1,
        uOut: 0,
        survNum: 1,
        mutChance: 0,
        ratio: 0,
        tourSize: 1,
        refPoints: 0,
        maskProb: 0,
        recNum: 0,

      }}   
      validationSchema={validate}
      onSubmit={(values, {resetForm}) => {
          const keys = Object.keys(values);
          for (let i = 0; i < keys.length; i++) {
            const key = keys[i];
            const isLastKey = i === keys.length - 1;
            updateState(key, values[key], isLastKey ? addParameter : undefined);
          }
          setCheck(true)
          resetForm()
    }}>
    {({ setFieldValue }) => (
      <Form className="add__wrapper">
          <div className="add__top">
              <h3>Добавить параметр генерации</h3>
              <div className="add__buttons">
                  <button className="add__add" type="submit">Добавить</button>
                  <Link to='/' className="add__return">Вернуться на главную</Link>
              </div>
          </div>
          <div className='add__content'>
            <div className="add__method">
              <div className="add__method-name">Метод генерации</div>
              <ul>
                {data.map((item, i) => {
                  return <li key={i} className={i === generationMethod ? "active" : ""} onClick={() => {updateState("generationMethod", i)}}>{item}</li>
                })}
              </ul>
            </div>
            <div className="add__base">
                    <TextField 
                    label="Минимальное количество входов"
                    type="number"
                    name="minInCount"
                    min={1}
                    />
                    <TextField 
                    label="Максимальное количество входов"
                    type="number"
                    name="maxInCount"
                    min={1}
                    />
                    <TextField 
                    label="Минимальное количество выходов"
                    type="number"
                    name="minOutCount"
                    min={1}
                    />
                    <TextField 
                    label="Максимальное количество выходов"
                    type="number"
                    name="maxOutCount"
                    min={1}
                    />
                    <TextField 
                    label="Количество повторений каждой комбинации"
                    type="number"
                    name="repeats"
                    min={1}
                    />
                    <div className="seed_and_random">
                      <TextField 
                      label="Сид генерации"
                      type="number"
                      name="seed"
                      min={-1}
                      />
                      <button type="button" onClick={() => setFieldValue("seed", Math.floor(Math.random() * UINT_MAX))}>
                        <img src={dice} width="35px" height="35px"/>
                      </button>
                    </div>
            </div>
            {generationMethod === 0 && <TruthTable state={state} updateState={updateState}/>}
            {generationMethod === 1 && <RandLevel updateState={updateState} maxLevel={maxLevel} maxElem={maxElem}/>}
            {generationMethod === 2 && <NumOperations
              state={state}
              updateState={updateState}
              numAnd={numAnd}
              numNand={numNand}
              numOr={numOr} 
              numNot={numNot}
              numNor={numNor} 
              numBuf={numBuf} 
              numXor={numXor}
              numXnor={numXnor}
            />}
            {generationMethod === 3 && <Genetic 
              geneticActive={geneticActive} updateState={updateState} 
              population={population}
              cycles={cycles}
              uOut={uOut}
              tourSize={tourSize}
              refPoints={refPoints}
              maskProb={maskProb}
              recNum={recNum}
              mutChance={mutChance}
              swapType={swapType}
              ratio={ratio}
              survNum={survNum}
            />}
            </div>
      </Form>
    )}
    </Formik>
  )
}


export default AddParameter