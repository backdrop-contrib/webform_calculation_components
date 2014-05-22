(function($, Drupal)
/**
 * @file
 * JavaScript behaviors for the calculation of selected webform component numbers.
 */
{
	// Our function name is prototyped as part of the Drupal.ajax namespace, adding to the commands:
	Drupal.ajax.prototype.commands.webformCalcNumberComponentAjaxCallback = function(ajax, response, status)
	{
		// The value we passed in our Ajax callback function will be available inside the
		// response object. Since we defined it as selectedValue in our callback, it will be
		// available in response.selectedValue. Usually we would not use an alert() function
		// as we could use ajax_command_alert() to do it without having to define a custom
		// ajax command, but for the purpose of demonstration, we will use an alert() function
		// here:
        console.log("response > %o",response);
        //alert("hello from webform calculation number component ajax commands");
        var operand_id = '#'+response.webformOperationDataArray['operand_id'];
        var operation = response.webformOperationDataArray['operation'];
        var result_id = '#'+response.webformOperationDataArray['result_id'];
        switch(operation) {
            case 'addition':
            var operation_result = Number($(result_id).val()) + Number($(operand_id).val());
            break;
            case 'subtraction':
            var operation_result = Number($(result_id).val()) - Number($(operand_id).val());
            break;
            case 'multiplication':
            var operation_result = Number($(result_id).val()) * Number($(operand_id).val());
            break;
            case 'division':
            var operation_result =  Number($(result_id).val()) / ((Number($(operand_id).val()) == 0)? 1 : Number($(operand_id).val()));
            break;
            case 'percentage':
            var operation_result = 0.01 * Number($(result_id).val()) * Number($(operand_id).val());
            break;
            case 'modulo':
            var operation_result =  Math.floor(Number($(result_id).val())) % ((Number($(operand_id).val()) == 0)? 1 : Number($(operand_id).val()));
            break;
        }
        //console.log("operation_id > %o",$(operand_id).val());
        //console.log("operation > %o",$(operation).val());
        $(result_id).val(operation_result);
        //console.log("result_id > %o",$(result_id).val());
	};
}(jQuery, Drupal));
