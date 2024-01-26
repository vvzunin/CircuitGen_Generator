import React from 'react'
import axios from 'axios';

import Scheme from './Scheme'

const DatasetItem = ({getDatasets, ready, id, parameters, currentProgress, isUpdating, setIsUpdating}) => {

  const isDone = 'is'+id+'Done';
  const status = !currentProgress
  ? 'error'
  : currentProgress.ready === currentProgress.in_total
  ? 'equal'
  : 'generation';


  if (status !== 'equal' && !isUpdating) {
    setIsUpdating(true);
  }
  if ((!localStorage.getItem(isDone) && ready) ||
      (localStorage.getItem(isDone) && status === 'error')) {
    localStorage.setItem(isDone, true);
    setIsUpdating(false);
  }

  // console.log('currentProgress: '+currentProgress)
  // console.log('id: '+id);
  // console.log('isDone: '+localStorage.getItem(isDone));
  // console.log('isUpdating: '+isUpdating);
  // console.log('status: '+status);
  // console.log('ready: '+ready);


  const deleteDataset = () => {
    axios.delete(`http://127.0.0.1:8000/api/datasets/${id}`)
    .then(() => {
      localStorage.removeItem(isDone);
      getDatasets();
      alert("Датасет успешно удален!");
      setIsUpdating(false);
    })
    .catch((e) => console.log(e));
  }


  return (
    <div className='dataset__wrapper'>
        <div className="dataset__info">
            <span>Датасет #{id}</span>
            <button className='parameter__delete' onClick={deleteDataset}>Удалить</button>
            {
              !ready && (status === "error") && <p>Статус генерации: ...</p>
            }
            {
              !ready && (status === "generation") && <p>Статус генерации: {currentProgress?.ready} из {currentProgress?.in_total} схем</p>
            }
            {
              ready && <p>Статус генерации: завершена</p>
            }
        </div>
        <div className="dataset__content">
            {parameters && parameters.map((item, i) => {
              return <Scheme data={item} key={i}/>
            })}
        </div>
    </div>
  )
}

export default DatasetItem