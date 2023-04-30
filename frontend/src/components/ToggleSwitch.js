import React from 'react'
import { useId } from "react-id-generator";


const ToggleSwitchFilter = ({changeParentState}) => {

	const [htmlId] = useId();
	const [checked, setChecked] = React.useState(false);	

	function changeCheckbox() {
	   setChecked(!checked);
	   {changeParentState && changeParentState(!checked);}
	}

	return (
	<div className="toggleSwitch">
		<input type="checkbox" id={htmlId} checked={checked} onChange={changeCheckbox}/>
        <label htmlFor={htmlId} className={checked ? "active" : ""}>Toggle</label>
	</div>
	)
}

export default ToggleSwitchFilter;