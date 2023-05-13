import React from 'react'
import axios from 'axios';

import Scheme from './Scheme'

const DatasetItem = ({id, parameters, currentProgress, getDatasets}) => {

  const [status, setStatus] = React.useState(null);

  React.useEffect(() => {
    if (!currentProgress) {
      setStatus('error');
    } else {
      if (currentProgress.ready == currentProgress.in_total) {
        setStatus('equal')
      } else {
        setStatus('generation')
      }
    }
  }, [])

  const deleteDataset = () => {
    axios.delete(`http://127.0.0.1:8000/api/datasets/${id}`)
    .then(() => {
      alert("Датасет успешно удален!");
      getDatasets();}
    )
    .catch((e) => console.log(e));
  }
  

  return (
    <div className='dataset__wrapper'>
        <div className="dataset__info">
            <span>Датасет #{id}</span>
            <button className='parametr__delete' onClick={deleteDataset}>Удалить</button>
            {
              (status === "error") && <p>Статус генерации: ошибка генерации</p>
            }
            {
              (status === "equal") && <p>Статус генерации: генерация завершена</p>
            }
            {
              (status === "generation") && <p>Статус генерации: сгенерировано {currentProgress?.ready} из {currentProgress?.in_total} схем</p>
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