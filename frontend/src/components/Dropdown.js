import React from 'react'

import arrow from '../assets/arrow.svg';

const Dropdown = ({data, setActiveParentValue}) => {

    const [active, setActive] = React.useState(0);
    const [isOpen, setIsOpen] = React.useState(false);

    const changeActive = i => {
        setActive(i);
        setActiveParentValue(data[i]);
        setIsOpen(false);
    }

    const setOpen = () => {
        if (data.length > 1) {setIsOpen(!isOpen)}
    }

    return (
    <div className="dropdown__wrapper">
        <div className="dropdown__active" onClick={setOpen}>
            <p>{data[active]}</p>
            {data.length > 1 && <img src={arrow} alt="arrow" className={isOpen ? 'active' : ''}/>}
        </div>
        {isOpen && <ul className="dropdown__list">
            {data.map((item, i) => {
                if (i === active) {
                    return null;
                }
                else {
                    return <li key={i} onClick={() => changeActive(i)}>{item}</li>;
                }
            })}
        </ul>}
    </div>
    )
}

export default Dropdown;