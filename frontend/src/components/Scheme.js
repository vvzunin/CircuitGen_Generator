import React from 'react'

const Scheme = () => {

    const [isOpen, setIsOpen] = React.useState(false);

    return (
    <div className='scheme__wrapper'>
        <div className='scheme__main'>
            <div className="scheme__name">
                Схема #1
            </div>
            <div className="scheme__buttons">
                <button className='scheme__more' onClick={() => setIsOpen(!isOpen)}>{isOpen ? 'Скрыть' : 'Подробнее'}</button>
                <button className='scheme__show'>Просмотреть</button>
            </div>
        </div>
        <div className={isOpen ? "scheme__info active" : "scheme__info"}>
            <div className="scheme__line"></div>
            <ul>
                <li>Минимальное количество входов: 5</li>
                <li>Минимальное количество выходов: 3</li>
                <li>Тип генерации: FromRandom</li>
            </ul>
        </div>
    </div>
    )
}

export default Scheme;