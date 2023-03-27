import React from 'react'

const Parametr = () => {

    const [isOpen, setIsOpen] = React.useState(false);

    return (
    <div className='parametr__wrapper'>
    <div className='parametr__main'>
        <div className="parametr__name">
            Параметр генерации #2
        </div>
        <div className="parametr__buttons">
            <button className='parametr__more' onClick={() => setIsOpen(!isOpen)}>{isOpen ? 'Скрыть' : 'Подробнее'}</button>
            <button className='parametr__delete'>Удалить</button>
        </div>
    </div>
    <div className={isOpen ? "parametr__info active" : "parametr__info"}>
        <div className="parametr__line"></div>
        <ul>
            <li>Минимальное количество входов: 5</li>
            <li>Минимальное количество выходов: 3</li>
            <li>Тип генерации: FromRandom</li>
        </ul>
    </div>
    </div>
    )
}

export default Parametr;