

				
				.extern	_start
				.extern	_stack_end
				
				
				.section	.vector
				
				.long	_start			/* パワーオンリセット */
				.long	_stack_end
				.long	_start			/* マニュアルリセット */
				.long	_stack_end

				.end

