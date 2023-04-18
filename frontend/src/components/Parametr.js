import React from 'react'

const Parametr = ({id, method, minInCount, maxInCount, minOutCount, maxOutCount, repeats, deleteParametr}) => {

    const [isOpen, setIsOpen] = React.useState(false);

    return (
    <div className='parametr__wrapper'>
    <div className='parametr__main'>
        <div className="parametr__name">
            Параметр генерации #{id}
        </div>
        <div className="parametr__buttons">
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