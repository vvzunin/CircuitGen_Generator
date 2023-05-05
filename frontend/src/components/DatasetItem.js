import React from 'react'
import Scheme from './Scheme'

const DatasetItem = ({id, parameters, currentProgress}) => {

  const [status, setStatus] = React.useState(null);

  React.useEffect(() => {
    if (!currentProgress) {
      setStatus('error');
    } else {
      if (currentProgress.ready == currentProgress.total) {
        setStatus('equal')
      } else {
        setStatus('generation')
      }
    }
  }, [])
  

  return (
    <div className='dataset__wrapper'>
        <div className="dataset__info">
            <span>Датасет #{id}</span>
            {
              (status === "error") && <p>Статус генерации: ошибка генерации</p>
            }
            {
              (status === "equal") && <p>Статус генерации: генерация завершена</p>
            }
            {
              (status === "generation") && <p>Статус генерации: сгенерировано {currentProgress?.ready} из {currentProgress?.total} схем</p>
            }
        </div>
        <div className="dataset__content">
            {parameters && parameters.map((item, i) => {
              return <Scheme id={item} key={i}/>
            })}
        </div>
    </div>
  )
}

export default DatasetItem