import React from 'react'

import gearImg from '../assets/gear.svg';
import select from '../assets/select.svg';
import noselect from '../assets/noselect.svg';

const Parametr = ({id, method, minInCount, maxInCount, minOutCount, maxOutCount, repeats, deleteParametr, gear}) => {

    const [isOpen, setIsOpen] = React.useState(false);

    const [status, setStatus] = React.useState('noselect');

    React.useEffect(() => {
        if (gear) {
            setStatus('gear');
        }
    }, [gear])
    

    return (
    <div className='parametr__wrapper'>
    <div className='parametr__main'>
        <div className="parametr__name">
            Параметр генерации #{id}
        </div>
        <div className="parametr__buttons">
            {status && (status == 'gear') && <div className="parametr__status gear">
                <img src={gearImg}/>
            </div>}
            {status && (status == 'select') && <div className="parametr__status select" onClick={() => setStatus('noselect')}>
                <img src={select}/>
            </div>}
            {status && (status == 'noselect') && <div className="parametr__status noselect" onClick={() => setStatus('select')}>
                <img src={noselect}/>
            </div>}
            <button className='parametr__more' onClick={() => setIsOpen(!isOpen)}>{isOpen ? 'Скрыть' : 'Подробнее'}</button>
            <button className='parametr__delete'onClick={() => deleteParametr()}>Удалить</button>
        </div>
    </div>
    <div className={isOpen ? "parametr__info active" : "parametr__info"}>
        <div className="parametr__line"></div>
        <ul>
            <li>Тип генерации: {method}</li>
            <li>Минимальное количество входов: {minInCount}</li>
            <li>Максимальное количество входов: {maxInCount}</li>
            <li>Минимальное количество выходов: {minOutCount}</li>
            <li>Максимальное количество выходов: {maxOutCount}</li>
            <li>Количество повторений каждой комбинации: {repeats}</li>
        </ul>
    </div>
    </div>
    )
}

export default Parametr;