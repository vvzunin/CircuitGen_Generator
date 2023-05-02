import React from 'react'
import Scheme from './Scheme'

const DatasetItem = ({id}) => {
  return (
    <div className='dataset__wrapper'>
        <div className="dataset__info">
            <span>Датасет #{id}</span>
        </div>
        <div className="dataset__content">
            <Scheme/>
            <Scheme/>
            <Scheme/>
        </div>
    </div>
  )
}

export default DatasetItem