import React from 'react'
import { useId } from "react-id-generator";


const ToggleSwitchFilter = ({changeParentState, isChecked = false}) => {

	const [htmlId] = useId();	

	function changeCheckbox() {
	   {changeParentState && changeParentState(!isChecked);}
	}

	return (
	<div className="toggleSwitch">
		<input type="checkbox" id={htmlId} checked={isChecked} onChange={changeCheckbox}/>
        <label htmlFor={htmlId} className={isChecked ? "active" : ""}>Toggle</label>
	</div>
	)
}

export default ToggleSwitchFilter;